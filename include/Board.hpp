#pragma once

#include <array>
#include <string>
#include <cstdint>

enum class Piece : uint8_t {
    EMPTY = 0,
    W_PAWN,
    W_KNIGHT,
    W_BISHOP,
    W_ROOK,
    W_QUEEN,
    W_KING,
    B_PAWN,
    B_KNIGHT,
    B_BISHOP,
    B_ROOK,
    B_QUEEN,
    B_KING
};

class Board {
public:
    Board();
    Board(const std::string& board);

    Piece at(uint16_t x, uint16_t y) const;

    bool empty(uint16_t x, uint16_t y) const;
    bool move(uint16_t x, uint16_t y, uint16_t xx, uint16_t yy);

private:
    static bool _valid_pos(uint16_t x, uint16_t y);
    static bool _valid_pos(uint16_t index);

    static uint16_t _convert_to_1d(uint16_t x, uint16_t y); 

    static Piece _convert_to_piece(const char c);
    static char _convert_to_char(Piece piece);

private:
    std::array<uint8_t, 64> board;

};