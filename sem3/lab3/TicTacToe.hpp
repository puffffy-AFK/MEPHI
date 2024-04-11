#pragma once

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <limits>


class TicTacToe {
public:
    TicTacToe(int n) : board(n, std::vector<char>(n, ' ')), size(n) {}

    bool makeMove(int x, int y, char player) {
        if (board[x][y] == ' ') {
            board[x][y] = player;
            return true;
        }
        return false;
    }

    void printBoard() {
        for (const auto &row : board) {
            for (const auto &cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
    }

    int evaluate() {
        if (isWinning('O')) return size;  // AI player wins
        if (isWinning('X')) return -size; // Human player wins

        int score = 0;
        score += countPotentialWins('O') - countPotentialWins('X');

        return score; // Draw or game not finished
    }

    bool isMovesLeft() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == ' ')
                    return true;
            }
        }
        return false;
    }

    bool isWinning(char player) {
        // Check rows and columns
        for (int i = 0; i < size; i++) {
            if (std::all_of(board[i].begin(), board[i].end(), [player](char c){ return c == player; })) return true;
            if (std::all_of(board.begin(), board.end(), [player, i](const std::vector<char>& row){ return row[i] == player; })) return true;
        }

        // Check diagonals
        bool diag1 = true, diag2 = true;
        for (int i = 0; i < size; i++) {
            if (board[i][i] != player) diag1 = false;
            if (board[i][size-i-1] != player) diag2 = false;
        }
        if (diag1 || diag2) return true;

        return false;
    }

    bool isFull() {
        for (const auto &row : board) {
            if (std::any_of(row.begin(), row.end(), [](char c){ return c == ' '; })) return false;
        }
        return true;
    }

    int getSize() const {
        return size;
    }

    char getCell(int i, int j) const {
        return board[i][j];
    }

    void setCell(int i, int j, char val) {
        board[i][j] = val;
    }

    bool isValidMove(int x, int y) const {
        // Check if the cell is within the board and is empty
        return x >= 0 && x < size && y >= 0 && y < size && board[x][y] == ' ';
    }

    int countPotentialWins(char player) {
        int count = 0;
        // Check rows and columns
        for (int i = 0; i < size; i++) {
            int row_count = 0;
            int col_count = 0;
            for (int j = 0; j < size; j++) {
                if (board[i][j] == player || board[i][j] == ' ') row_count++;
                if (board[j][i] == player || board[j][i] == ' ') col_count++;
            }
            if (row_count == size) count++;
            if (col_count == size) count++;
        }

        // Check diagonals
        int diag1_count = 0, diag2_count = 0;
        for (int i = 0; i < size; i++) {
            if (board[i][i] == player || board[i][i] == ' ') diag1_count++;
            if (board[i][size-i-1] == player || board[i][size-i-1] == ' ') diag2_count++;
        }
        if (diag1_count == size) count++;
        if (diag2_count == size) count++;

        return count;
    }

private:
    std::vector<std::vector<char>> board;
    int size;
};

int minimax(TicTacToe &game, int depth, bool isMax, int alpha, int beta) {
    int score = game.evaluate();

    // If Maximizer has won the game return his/her evaluated score
    if (score == game.getSize())
        return score;

    // If Minimizer has won the game return his/her evaluated score
    if (score == -game.getSize())
        return score;

    // If there are no more moves and no winner then it is a tie
    if (!game.isMovesLeft())
        return 0;

    // If this maximizer's move
    if (isMax) {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < game.getSize(); i++) {
            for (int j = 0; j < game.getSize(); j++) {
                // Check if cell is empty
                if (game.getCell(i, j) == ' ') {
                    // Make the move
                    game.setCell(i, j, 'X');

                    // Call minimax recursively and choose the maximum value
                    best = std::max(best, minimax(game, depth + 1, !isMax, alpha, beta));

                    // Undo the move
                    game.setCell(i, j, ' ');

                    alpha = std::max(alpha, best);
                    if (beta <= alpha)
                        return best;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < game.getSize(); i++) {
            for (int j = 0; j < game.getSize(); j++) {
                // Check if cell is empty
                if (game.getCell(i, j) == ' ') {
                    // Make the move
                    game.setCell(i, j, 'O');

                    // Call minimax recursively and choose the minimum value
                    best = std::min(best, minimax(game, depth + 1, !isMax, alpha, beta));

                    // Undo the move
                    game.setCell(i, j, ' ');

                    beta = std::min(beta, best);
                    if (beta <= alpha)
                        return best;
                }
            }
        }
        return best;
    }
}

std::pair<int, int> findBestMove(TicTacToe &game) {
    int bestScore = INT_MIN;
    std::pair<int, int> move = {-1, -1};

    // Traverse all cells, evaluate minimax function for all empty cells
    for (int i = 0; i < game.getSize(); i++) {
        for (int j = 0; j < game.getSize(); j++) {
            // Check cell is empty
            if (game.getCell(i, j) == ' ') {
                // Check if the move is within a certain radius of an existing move
                bool nearExistingMove = false;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int x = i + dx, y = j + dy;
                        if (x >= 0 && x < game.getSize() && y >= 0 && y < game.getSize() && game.getCell(x, y) != ' ') {
                            nearExistingMove = true;
                            break;
                        }
                    }
                    if (nearExistingMove) break;
                }
                if (!nearExistingMove) continue;

                // Make the move
                game.setCell(i, j, 'O');

                // compute evaluation function for this move.
                int moveScore = minimax(game, 0, false, -game.getSize(), game.getSize());

                // Undo the move
                game.setCell(i, j, ' ');

                // If the value of the current move is more than the best value, then update best
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}