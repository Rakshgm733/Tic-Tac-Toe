#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char player, ai;
    bool singlePlayer;

public:
    TicTacToe(bool isSinglePlayer) {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        player = 'X';
        ai = 'O';
        singlePlayer = isSinglePlayer;
    }

    void printBoard() {
        cout << "-------------\n";
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " | ";
            }
            cout << "\n-------------\n";
        }
    }

    bool isMovesLeft() {
        for (auto &row : board)
            for (char c : row)
                if (c == ' ')
                    return true;
        return false;
    }

    int evaluate() {
        for (int row = 0; row < 3; row++)
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == ai) return +10;
                else if (board[row][0] == player) return -10;
            }

        for (int col = 0; col < 3; col++)
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == ai) return +10;
                else if (board[0][col] == player) return -10;
            }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == ai) return +10;
            else if (board[0][0] == player) return -10;
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == ai) return +10;
            else if (board[0][2] == player) return -10;
        }

        return 0;
    }

    int minimax(int depth, bool isMax) {
        int score = evaluate();
        if (score == 10) return score - depth;
        if (score == -10) return score + depth;
        if (!isMovesLeft()) return 0;

        if (isMax) {
            int best = numeric_limits<int>::min();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = ai;
                        best = max(best, minimax(depth + 1, !isMax));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = player;
                        best = min(best, minimax(depth + 1, !isMax));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        }
    }

    pair<int, int> findBestMove() {
        int bestVal = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = ai;
                    int moveVal = minimax(0, false);
                    board[i][j] = ' ';
                    if (moveVal > bestVal) {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    void playGame() {
        int x, y, turn = 0;
        while (true) {
            printBoard();
            if (turn % 2 == 0 || !singlePlayer) {
                cout << "Player " << (turn % 2 == 0 ? 'X' : 'O') << ", enter your move (row and col): ";
                cin >> x >> y;
                if (x < 0 || y < 0 || x > 2 || y > 2 || board[x][y] != ' ') {
                    cout << "Invalid move. Try again.\n";
                    continue;
                }
                board[x][y] = (turn % 2 == 0) ? 'X' : 'O';
            } else {
                cout << "AI is making a move...\n";
                pair<int, int> aiMove = findBestMove();
                board[aiMove.first][aiMove.second] = ai;
            }

            int result = evaluate();
            if (result == 10 || result == -10 || !isMovesLeft()) {
                printBoard();
                if (result == 10) cout << "AI wins!\n";
                else if (result == -10) cout << "Player wins!\n";
                else cout << "It's a draw!\n";
                break;
            }

            turn++;
        }
    }
};

int main() {
    int mode;
    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Select mode: 1. Single Player  2. Multiplayer: ";
    cin >> mode;
    bool single = (mode == 1);
    TicTacToe game(single);
    game.playGame();
    return 0;
}
