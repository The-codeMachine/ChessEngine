#pragma once

#include <array>
#include <string>
#include <cstdint>

using Position = std::pair<int, int>;
using Move = std::pair<Position, Position>;

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
    Board(const std::string& FEN);

    Piece at(uint16_t x, uint16_t y) const;
    bool empty(uint16_t x, uint16_t y) const;
    Position enPassant() const noexcept;
    std::array<bool, 4> castling() const noexcept;

    bool move(uint16_t x, uint16_t y, uint16_t xx, uint16_t yy);

    std::string toString(bool pretty = false) const noexcept;

private:
    static bool _valid_pos(uint16_t x, uint16_t y);
    static bool _valid_pos(uint16_t index);

    static uint16_t _convert_to_1d(uint16_t x, uint16_t y); 

    static Piece _convert_to_piece(const char c);
    static char _convert_to_char(Piece piece);

    void _parse_FEN(const std::string &FEN);

    std::string _to_string() const noexcept;
    std::string _to_fen() const noexcept;

private:
    std::array<uint8_t, 64> _board;
    
    bool _turn; // white = true, black = false
    // 0 = white king side, 1 = white queen side
    // 2 = black king side, 3 = black queen side
    std::array<bool, 4> _castle_rights; 
    
    // location of the en passant piece
    // if invalid then == {-1, -1}
    Position _en_passant; 
    
    uint32_t _move_count; 
    uint32_t _half_clock_move_count;

};