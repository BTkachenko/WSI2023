#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <memory>

using namespace std;

struct Puzzle {
    vector<int> board;
    int g{}, h{};
    int zero_pos{};
    weak_ptr<Puzzle> parent;

    bool operator<(const Puzzle& other) const {
        return g + h > other.g + other.h;
    }
};

struct PuzzleHasher {
    size_t operator()(const Puzzle& puzzle) const {
        size_t hash = 0;
        for (int i : puzzle.board) {
            hash = hash * 31 + i;
        }
        return hash;
    }
};

bool operator==(const Puzzle& lhs, const Puzzle& rhs) {
    return lhs.board == rhs.board;
}

int misplaced_tiles(const Puzzle& puzzle) {
    int count = 0;
    for (size_t i = 0; i < puzzle.board.size(); i++) {
        if (puzzle.board[i] != 0 && puzzle.board[i] != i + 1) {
            count++;
        }
    }
    return count;
}

int manhattan_distance(const Puzzle& puzzle) {
    int distance = 0;
    for (size_t i = 0; i < puzzle.board.size(); i++) {
        if (puzzle.board[i] != 0) {
            int x = (puzzle.board[i] - 1) % 4;
            int y = (puzzle.board[i] - 1) / 4;
            distance += abs(x - static_cast<int>(i % 4)) + abs(y - static_cast<int>(i / 4));
        }
    }
    return distance;
}

const int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool is_valid_move(int x, int y) {
    return x >= 0 && x < 4 && y >= 0 && y < 4;
}

vector<Puzzle> get_neighbors(const Puzzle& puzzle, int (*heuristic)(const Puzzle&)) {
    int x = puzzle.zero_pos % 4;
    int y = puzzle.zero_pos / 4;

    vector<Puzzle> neighbors;
    for (const auto& move : moves) {
        int nx = x + move[0];
        int ny = y + move[1];
        if (is_valid_move(nx, ny)) {
            Puzzle neighbor = puzzle;
            swap(neighbor.board[y * 4 + x], neighbor.board[ny * 4 + nx]);
            neighbor.zero_pos = ny * 4 + nx;
            neighbor.g += 1;
            neighbor.h = heuristic(neighbor);
            neighbor.parent = make_shared<Puzzle>(puzzle); // Poprawiona linia
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}


vector<int> solve_puzzle(Puzzle start, int (*heuristic)(const Puzzle&)) {
    priority_queue<Puzzle> open;
    unordered_set<Puzzle, PuzzleHasher> closed;

    open.push(start);

    while (!open.empty()) {
        Puzzle current = open.top();
        open.pop();

        if (current.h == 0) {
            vector<int> solution;
            while (!current.parent.expired()) {
                int move = current.board[current.zero_pos];
                solution.push_back(move);
                current = *current.parent.lock();
            }
            reverse(solution.begin(), solution.end());
            return solution;
        }

        closed.insert(current);

        for (const auto& neighbor : get_neighbors(current, heuristic)) {
            if (closed.count(neighbor) == 0) {
                open.push(neighbor);
            }
        }
    }

    return {};
}

bool is_solvable(const vector<int>& board) {
    int inversions = 0;
    for (size_t i = 0; i < board.size(); i++) {
        if (board[i] != 0) {
            for (size_t j = i + 1; j < board.size(); j++) {
                if (board[j] != 0 && board[i] > board[j]) {
                    inversions++;
                }
            }
        } else {
            inversions += (i / 4) + 1;
        }
    }
    return inversions % 2 == 0;
}

void print_board(const vector<int>& board) {
    for (size_t i = 0; i < board.size(); i++) {
        cout << (board[i] == 0 ? "_" : to_string(board[i])) << " ";
        if (i % 4 == 3) {
            cout << endl;
        }
    }
}
int main() {
    srand(time(nullptr));

    vector<int> board(16);
    for (int i = 0; i < 15; i++) {
        board[i] = i + 1;
    }

    do {
        random_shuffle(board.begin(), board.end() - 1);
    } while (!is_solvable(board));

    Puzzle start;
    start.board = board;
    start.g = 0;
    start.parent.reset();

    for (size_t i = 0; i < start.board.size(); i++) {
        if (start.board[i] == 0) {
            start.zero_pos = i;
            break;
        }
    }
    cout << "Initial state:" << endl;
    print_board(start.board);

    // Choose heuristic function
    int (*heuristic)(const Puzzle&) = manhattan_distance;
    start.h = heuristic(start);

    vector<int> solution = solve_puzzle(start, heuristic);

    cout << "Solution:" << endl;
    for (int move : solution) {
        cout << move << " ";
    }
    cout << endl;

    cout << "Number of steps: " << solution.size() << endl;

    return 0;
}


