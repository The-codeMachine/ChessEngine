#pragma once

#include <Piece.hpp>

#include <string>

class Board {
public:
    Board() = default;
    Board(const std::string& board);

    const Piece& get(int x, int y) const;
    bool empty(int x, int y) const;

    bool move(int x, int y, int newX, int newY);

private:
    Piece board[8][8];

};