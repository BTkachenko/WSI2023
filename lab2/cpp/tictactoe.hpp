//Author: Bohdan Tkachenko 256630
#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <algorithm>

constexpr size_t BOARD_SIZE = 5;

constexpr std::array<std::array<std::pair<size_t, size_t>, 4>, 28> win = {{

                                                                                         { { {0,0}, {0,1}, {0,2}, {0,3} } },
                                                                                         { { {1,0}, {1,1}, {1,2}, {1,3} } },
                                                                                 {{ {2,0}, {2,1}, {2,2}, {2,3} } },
                                                                                 {       { {3,0}, {3,1}, {3,2}, {3,3} } },
                                                                                 {       { {4,0}, {4,1}, {4,2}, {4,3} } },
                                                                                 {       { {0,1}, {0,2}, {0,3}, {0,4} } },
                                                                                 {       { {1,1}, {1,2}, {1,3}, {1,4} } },
                                                                                 {       { {2,1}, {2,2}, {2,3}, {2,4} } },
                                                                                 {       { {3,1}, {3,2}, {3,3}, {3,4} } },
                                                                                 {       { {4,1}, {4,2}, {4,3}, {4,4} } },
                                                                                 {       { {0,0}, {1,0}, {2,0}, {3,0} } },
                                                                                 {       { {0,1}, {1,1}, {2,1}, {3,1} } },
                                                                                 {       { {0,2}, {1,2}, {2,2}, {3,2} } },
                                                                                 {       { {0,3}, {1,3}, {2,3}, {3,3} } },
                                                                                 {       { {0,4}, {1,4}, {2,4}, {3,4} } },
                                                                                 {       { {1,0}, {2,0}, {3,0}, {4,0} } },
                                                                                 {       { {1,1}, {2,1}, {3,1}, {4,1} } },
                                                                                 {       { {1,2}, {2,2}, {3,2}, {4,2} } },
                                                                                 {       { {1,3}, {2,3}, {3,3}, {4,3} } },
                                                                                 {       { {1,4}, {2,4}, {3,4}, {4,4} } },
                                                                                 {       { {0,1}, {1,2}, {2,3}, {3,4} } },
                                                                                 {       { {0,0}, {1,1}, {2,2}, {3,3} } },
                                                                                 {       { {1,1}, {2,2}, {3,3}, {4,4} } },
                                                                                 {       { {1,0}, {2,1}, {3,2}, {4,3} } },
                                                                                 {       { {0,3}, {1,2}, {2,1}, {3,0} } },
                                                                                 {       { {0,4}, {1,3}, {2,2}, {3,1} } },
                                                                                 {       { {1,3}, {2,2}, {3,1}, {4,0} } },
                                                                                 {       { {1,4}, {2,3}, {3,2}, {4,1} } }
                                                                                 }};

constexpr std::array<std::array<std::pair<size_t, size_t>, 3>, 48> lose = {{
                                                                                           {{std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2)}},
                                                                                           {{std::make_pair(0, 1), std::make_pair(0, 2), std::make_pair(0, 3)}},
                                                                                           {{std::make_pair(0, 2), std::make_pair(0, 3), std::make_pair(0, 4)}},
                                                                                           {{std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(1, 2)}},
                                                                                           {{std::make_pair(1, 1), std::make_pair(1, 2), std::make_pair(1, 3)}},
                                                                                           {{std::make_pair(1, 2), std::make_pair(1, 3), std::make_pair(1, 4)}},
                                                                                           {{std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(2, 2)}},
                                                                                           {{std::make_pair(2, 1), std::make_pair(2, 2), std::make_pair(2, 3)}},
                                                                                           {{std::make_pair(2, 2), std::make_pair(2, 3), std::make_pair(2, 4)}},
                                                                                           {{std::make_pair(3, 0), std::make_pair(3, 1), std::make_pair(3, 2)}},
                                                                                           {{std::make_pair(3, 1), std::make_pair(3, 2), std::make_pair(3, 3)}},
                                                                                           {{std::make_pair(3, 2), std::make_pair(3, 3), std::make_pair(3, 4)}},
                                                                                           {{std::make_pair(4, 0), std::make_pair(4, 1), std::make_pair(4, 2)}},
                                                                                           {{std::make_pair(4, 1), std::make_pair(4, 2), std::make_pair(4, 3)}},
                                                                                           {{std::make_pair(4, 2), std::make_pair(4, 3), std::make_pair(4, 4)}},
                                                                                           {{std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(2, 0)}},
                                                                                           {{std::make_pair(1, 0), std::make_pair(2, 0), std::make_pair(3, 0)}},
                                                                                           {{std::make_pair(2, 0), std::make_pair(3, 0), std::make_pair(4, 0)}},
                                                                                           {{std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(2, 1)}},
                                                                                           {{std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1)}},
                                                                                           {{std::make_pair(2, 1), std::make_pair(3, 1), std::make_pair(4, 1)}},
                                                                                           {{std::make_pair(0, 2), std::make_pair(1, 2), std::make_pair(2, 2)}},
                                                                                           {{std::make_pair(1, 2), std::make_pair(2, 2), std::make_pair(3, 2)}},
                                                                                           {{std::make_pair(2, 2), std::make_pair(3, 2), std::make_pair(4, 2)}},
                                                                                           {{std::make_pair(0, 3), std::make_pair(1, 3), std::make_pair(2, 3)}},
                                                                                           {{std::make_pair(1, 3), std::make_pair(2, 3), std::make_pair(3, 3)}},
                                                                                           {{std::make_pair(2, 3), std::make_pair(3, 3), std::make_pair(4, 3)}},
                                                                                           {{std::make_pair(0, 4), std::make_pair(1, 4), std::make_pair(2, 4)}},
                                                                                           {{std::make_pair(1, 4), std::make_pair(2, 4), std::make_pair(3, 4)}},
                                                                                           {{std::make_pair(2, 4), std::make_pair(3, 4), std::make_pair(4, 4)}},
                                                                                           {{std::make_pair(0, 2), std::make_pair(1, 3), std::make_pair(2, 4)}},
                                                                                           {{std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3)}},
                                                                                           {{std::make_pair(1, 2), std::make_pair(2, 3), std::make_pair(3, 4)}},
                                                                                           {{std::make_pair(0, 0), std::make_pair(1, 1), std::make_pair(2, 2)}},
                                                                                           {{std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)}},
                                                                                           {{std::make_pair(2, 2), std::make_pair(3, 3), std::make_pair(4, 4)}},
                                                                                           {{std::make_pair(1, 0), std::make_pair(2, 1), std::make_pair(3, 2)}},
                                                                                           {{std::make_pair(2, 1), std::make_pair(3, 2), std::make_pair(4, 3)}},
                                                                                           {{std::make_pair(2, 0), std::make_pair(3, 1), std::make_pair(4, 2)}},
                                                                                           {{std::make_pair(0, 2), std::make_pair(1, 1), std::make_pair(2, 0)}},
                                                                                           {{std::make_pair(0, 3), std::make_pair(1, 2), std::make_pair(2, 1)}},
                                                                                           {{std::make_pair(1, 2), std::make_pair(2, 1), std::make_pair(3, 0)}},
                                                                                           {{std::make_pair(0, 4), std::make_pair(1, 3), std::make_pair(2, 2)}},
                                                                                           {{std::make_pair(1, 3), std::make_pair(2, 2), std::make_pair(3, 1)}},
                                                                                           {{std::make_pair(2, 2), std::make_pair(3, 1), std::make_pair(4, 0)}},
                                                                                           {{std::make_pair(1, 4), std::make_pair(2, 3), std::make_pair(3, 2)}},
                                                                                           {{std::make_pair(2, 3), std::make_pair(3, 2), std::make_pair(4, 1)}},
                                                                                           {{std::make_pair(2, 4), std::make_pair(3, 3), std::make_pair(4, 2)}}
                                                                                   }};


size_t other(size_t p) {
    if (p == 1) {
        return 2;
    } else {
        return 1;
    }
}

class GameState {
public:
    std::array<std::array<size_t, BOARD_SIZE>, BOARD_SIZE> board;
    size_t turn;

    GameState() : board{}, turn(1) {
        // Initialize the game board
        for (auto& row : board) {
            for (auto& cell : row) {
                cell = 0;
            }
        }
    }

    void print_board() {
        // Print the game board
        for (const auto& row : board) {
            for (const auto& cell : row) {
                switch (cell) {
                    case 1:
                        std::cout << "X ";
                        break;
                    case 2:
                        std::cout << "O ";
                        break;
                    default:
                        std::cout << "_ ";
                        break;
                }
            }
            std::cout << std::endl;
        }
    }

    void make_move(std::pair<size_t, size_t> destination) {
        // Make a move on the game board
        board[destination.first][destination.second] = turn;
        turn = other(turn);
    }

    bool check_win(size_t player) {
        for (const auto& caseSet : win) {
            bool hasWon = true;
            for (const auto& cell : caseSet) {
                if (board[cell.first][cell.second] != player) {
                    hasWon = false;
                    break;
                }
            }
            if (hasWon) {
                return true;
            }
        }
        return false;
    }

    bool check_loose(size_t player) {
        // Check if the player has lost
        for (const auto& caseSet : lose) {
            bool hasLost = true;
            for (const auto& cell : caseSet) {
                if (board[cell.first][cell.second] != player) {
                    hasLost = false;
                    break;
                }
            }
            if (hasLost) {
                return true;
            }
        }
        return false;
    }

    std::vector<GameState> successors() {
        // Generate successor states
        std::vector<GameState> successors;
        for (size_t i = 0; i < BOARD_SIZE; ++i) {
            for (size_t j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == 0) {
                    GameState successor = *this;
                    successor.make_move(std::make_pair(i, j));
                    successors.push_back(successor);
                }
            }
        }
        return successors;
    }

    bool is_over() {
        // Check if the game in the finishing state
        return check_win(1) || check_loose(1) || check_win(2) || check_loose(2);
    }

    int count_oneoff(size_t player) {
        // Count one-off moves for the player
        int count = 0;
        for (size_t row = 0; row < BOARD_SIZE; ++row) {
            for (size_t col = 0; col < BOARD_SIZE - 3; ++col) {
                if (board[row][col] == player && board[row][col + 1] == player && board[row][col + 3] == player && board[row][col + 2] == 0) {
                    count += 1;
                }
                if (board[row][col] == player && board[row][col + 2] == player && board[row][col + 3] == player && board[row][col + 1] == 0) {
                    count += 1;
                }
            }
        }
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            for (size_t row = 0; row < BOARD_SIZE - 3; ++row) {
                if (board[row][col] == player && board[row + 1][col] == player && board[row + 3][col] == player && board[row + 2][col] == 0) {
                    count += 1;
                }
                if (board[row][col] == player && board[row + 2][col] == player && board[row + 3][col] == player && board[row + 1][col] == 0) {
                    count += 1;
                }
            }
        }
        return count;
    }

    int evaluate() {
        // Evaluate the state
        size_t p = other(turn);

        // Return the maximum heuristic value if a player wins or the other player loses
        if (check_win(p) || check_loose(other(p))) {
            return std::numeric_limits<int>::max();
        }
        if (check_win(other(p)) || check_loose(p)) {
            return std::numeric_limits<int>::min();
        }

        int score = count_oneoff(p) * 49;
        score -= count_oneoff(other(p)) * 49;

        return score;
    }
};

int minimax(GameState state, size_t depth, bool maximize, int alpha, int beta) {
    if (depth == 0 || state.is_over()) {
        int eval = state.evaluate();
        return eval;
    }

    if (maximize) {
        int val = std::numeric_limits<int>::min();

        for (const auto& successor : state.successors()) {
            val = std::max(val, minimax(successor, depth - 1, false, alpha, beta));
            alpha = std::max(alpha, val);
            if (val > beta) {
                break;
            }
        }

        return val;
    } else {
        int val = std::numeric_limits<int>::max();

        for (const auto& successor : state.successors()) {
            val = std::min(val, minimax(successor, depth - 1, true, alpha, beta));
            beta = std::min(beta, val);
            if (val < alpha) {
                break;
            }
        }

        return val;
    }
}


std::pair<size_t, size_t> move_with_minimax(const GameState& state, size_t depth) {
    std::vector<std::pair<int, std::pair<size_t, size_t>>> options;
    std::pair<size_t, size_t> mv;

    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            if (state.board[i][j] == 0) {
                GameState tmp_game_state = state;
                tmp_game_state.make_move(std::make_pair(i, j));
                if (!tmp_game_state.check_loose(other(state.turn))) {
                    options.emplace_back(minimax(tmp_game_state, depth - 1, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), std::make_pair(i, j));
                }
            }
        }
    }

    std::sort(options.begin(), options.end(), [](const std::pair<int, std::pair<size_t, size_t>>& a, const std::pair<int, std::pair<size_t, size_t>>& b) {
        return b.first < a.first;
    });

    if (!options.empty()) {
        int min = options[0].first;
        std::vector<std::pair<size_t, size_t>> choices;

        for (const auto& option : options) {
            if (option.first == min) {
                choices.push_back(option.second);
            }
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(0, choices.size() - 1);

        mv = choices[dis(gen)];
    }

    return mv;
}





