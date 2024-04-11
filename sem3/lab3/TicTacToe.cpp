#include <iostream>

#include "TicTacToe.hpp"
#include "TestTic.hpp"

int main() {
    test();
    int size;
    std::cout << "Enter board size: ";
    while(!(std::cin >> size) || size <= 0) {
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    TicTacToe game(size);
    char player = 'X';
    while (true) {
        game.printBoard();
        if (player == 'X') {
            int x, y;
            std::cout << "Enter your move (x y): ";
            while(!(std::cin >> x >> y) || x < 0 || x >= size || y < 0 || y >= size || !game.isValidMove(x, y)) {
                std::cout << "Invalid move. Please enter a valid move (x y): ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            game.makeMove(x, y, player);
        } else {
            auto [x, y] = findBestMove(game);
            game.makeMove(x, y, player);
        }
        if (game.isWinning(player)) {
            game.printBoard();
            std::cout << "Player " << player << " wins!\n";
            break;
        } else if (game.isFull()) {
            game.printBoard();
            std::cout << "It's a draw!\n";
            break;
        }
        player = (player == 'X' ? 'O' : 'X');
    }

    return 0;
}