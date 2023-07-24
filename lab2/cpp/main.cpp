//Author: Bohdan Tkachenko 256630


#include <iostream>

#include <array>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "tictactoe.hpp"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Wrong args supplied" << std::endl;
        return 1;
    }
    std::string ip = argv[1];
    std::string port = argv[2];
    size_t player = std::stoi(argv[3]);
    size_t depth = std::stoi(argv[4]);
    std::cout << ip << ", " << port << ", " << player << ", " << depth << std::endl;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(std::stoi(port));
    if (inet_pton(AF_INET, ip.c_str(), &(serverAddr.sin_addr)) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        return 1;
    }

    if (connect(sock, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    std::cout << "Successfully connected to server" << std::endl;
    char data[3];
    GameState gameBoard;
    while (true) {
        std::memset(data, 9, sizeof(data));
        ssize_t bytesRead = recv(sock, data, sizeof(data), 0);
        if (bytesRead <= 0) {
            std::cerr << "Failed to receive data" << std::endl;
            break;
        }
        std::string msg_in(data, bytesRead);
        std::cout << msg_in << std::endl;

        if (data[2] == 9) {
            auto row = static_cast<size_t>(data[0] - '1');
            auto col = static_cast<size_t>(data[1] - '1');
            gameBoard.make_move(std::make_pair(row, col));
            std::pair<size_t, size_t> mv = move_with_minimax(gameBoard, depth);
            gameBoard.make_move(mv);
            std::stringstream ss;
            ss << (mv.first + 1) << (mv.second + 1);
            std::string move = ss.str();
            if (send(sock, move.c_str(), move.length(), 0) != move.length()) {
                std::cerr << "Failed to send move" << std::endl;
                break;
            }
        } else if (msg_in == "600") {
            std::pair<size_t, size_t> mv = move_with_minimax(gameBoard, depth);
            gameBoard.make_move(mv);
            std::stringstream ss;
            ss << (mv.first + 1) << (mv.second + 1);
            std::string move = ss.str();
            if (send(sock, move.c_str(), move.length(), 0) != move.length()) {
                std::cerr << "Failed to send move" << std::endl;
                break;
            } else if (msg_in == "700") {
                std::string playerStr = std::to_string(player);
                if (send(sock, playerStr.c_str(), playerStr.length(), 0) != playerStr.length()) {
                    std::cerr << "Failed to send player" << std::endl;
                    break;
                }
            } else {
                break;
            }
        }
    }

    close(sock);
    std::cout << "Terminated." << std::endl;

    return 0;
}
