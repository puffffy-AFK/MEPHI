#pragma once

#include <cassert>
#include <sstream>


#include "TicTacToe.hpp"

// Mock version of TicTacToe class
class MockTicTacToe : public TicTacToe {
public:
    MockTicTacToe(int size) : TicTacToe(size) {}

    void makeMove(int x, int y, char player) {
        TicTacToe::makeMove(x, y, player);
    }

    bool isWinning(char player) {
        return TicTacToe::isWinning(player);
    }

    bool isFull() {
        return TicTacToe::isFull();
    }

    bool isValidMove(int x, int y) {
        return TicTacToe::isValidMove(x, y);
    }
};

std::pair<int, int> mockFindBestMove(TicTacToe& game) {
    return {1, 1}; // Always return the center position
}


void test() {
    MockTicTacToe game(3);
    char player = 'X';

    std::vector<std::pair<int, int>> moves = {{0, 0}, {2, 0}, {0, 2}, {1, 2}};

    for (const auto& [x, y] : moves) {
        assert(game.isValidMove(x, y));
        game.makeMove(x, y, player);
        if (game.isWinning(player)) {
            assert(player == 'O');
            break;
        } else if (game.isFull()) {
            assert(false); // The game should not be a draw
            break;
        }
        player = (player == 'X' ? 'O' : 'X');
    }
    std::cout << "Tests passed!\n";
}
