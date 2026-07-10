#include "../include/Board.hpp"

const Piece& Board::get(int x, int y) const {
    return board[x][y];
}

bool Board::empty(int x, int y) const {
    return get(x, y).value() == -1;
}

bool Board::move(int x, int y, int newX, int newY) {
    if (empty(x, y))
        return false;

    return board[x][y].move(newX, newY);
}