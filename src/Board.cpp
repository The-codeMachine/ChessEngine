#include "../include/Board.hpp"

#include <stdexcept>

Board::Board() {
    std::string board = 
    "RNBQKBNR"
    "PPPPPPPP"
    "        "
    "        "
    "        "
    "        "
    "pppppppp"
    "rnbqkbnr";

    Board(board);
}

Board::Board(const std::string &board) {
    if (board.size() != 64) {
        throw std::runtime_error("Failed to construct board: "
                                 "initialization size is not equal to 64 (8 x 8 grid)");
    }

    for (uint8_t i = 0; i < 64; ++i) {
        this->board[i] = static_cast<uint8_t>(board[i]);
    }
}

Piece Board::at(uint16_t x, uint16_t y) const {
    if (!_valid_pos(x, y))
        throw std::runtime_error("(x, y) is not a valid position");

    return static_cast<Piece>(board[_convert_to_1d(x, y)]);
}

bool Board::empty(uint16_t x, uint16_t y) const {
    return at(x, y) == Piece::EMPTY;
}

bool Board::_valid_pos(uint16_t x, uint16_t y) {
    return _valid_pos(_convert_to_1d(x, y));
}

bool Board::_valid_pos(uint16_t index) {
    return index < 64;
}

uint16_t Board::_convert_to_1d(uint16_t x, uint16_t y) {
    return y * 8 + x;
} 

Piece Board::_convert_to_piece(const char c) {
    switch (c) {
        case ' ':
            return Piece::EMPTY;
        case 'P':
            return Piece::W_PAWN;
        case 'p':
            return Piece::B_PAWN;
        case 'R':
            return Piece::W_ROOK;
        case 'r':
            return Piece::B_ROOK;
        case 'N':
            return Piece::W_KNIGHT;
        case 'n':
            return Piece::B_KNIGHT;
        case 'B':
            return Piece::W_BISHOP;
        case 'b':
            return Piece::B_BISHOP;
        case 'Q':
            return Piece::W_QUEEN;
        case 'q':
            return Piece::B_QUEEN;
        case 'K':
            return Piece::W_KING;
        case 'k':
            return Piece::B_KING;

        default:
            break;
    }
}

char Board::_convert_to_char(Piece piece) {
    switch (piece) {
        case Piece::EMPTY: 
            return ' ';
        case Piece::W_PAWN: 
            return 'P';
        case Piece::B_PAWN: 
            return 'p';
        case Piece::W_ROOK: 
            return 'R';
        case Piece::B_ROOK: 
            return 'r';
        case Piece::W_KNIGHT: 
            return 'N';
        case Piece::B_KNIGHT: 
            return 'n';
        case Piece::W_BISHOP: 
            return 'B';
        case Piece::B_BISHOP: 
            return 'b';
        case Piece::W_QUEEN: 
            return 'Q';
        case Piece::B_QUEEN: 
            return 'q';
        case Piece::W_KING: 
            return 'K';
        case Piece::B_KING: 
            return 'k';
        default: 
            break;
    }
}