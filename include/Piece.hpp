#pragma once

#include <cstdint>

class Board;

class Piece {
public:
    Piece(int x, int y) :
        _x(x), _y(y), _white(false), _value(-1) {}
    Piece(int x, int y, bool white, int value) :
        _x(x), _y(y), _white(white), _value(value) {}

    virtual bool move(int x, int y);
    virtual void calculateValidMoves(Board& board) const noexcept;

    int value() const noexcept {
        return _value;
    }

private:
    int _value;

    bool _white;
    uint8_t _x, _y;

};