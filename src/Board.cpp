#include "../include/Board.hpp"

#include <sstream>
#include <stdexcept>
#include <cctype>

#include <iostream>

Board::Board() {
    std::string FEN = 
    "rnbqkbnr/pppppppp/8/8"
    "/8/8/PPPPPPPP/RNBQKBNR "
    "w KQkq - 0 1";

    _parse_FEN(FEN);
}

Board::Board(const std::string &FEN) {
    _parse_FEN(FEN);
}

Piece Board::at(uint16_t x, uint16_t y) const {
    if (!_valid_pos(x, y))
        throw std::runtime_error("(x, y) is not a valid position");

    return static_cast<Piece>(_board[_convert_to_1d(x, y)]);
}

bool Board::empty(uint16_t x, uint16_t y) const {
    return at(x, y) == Piece::EMPTY;
}

std::string Board::toString(bool pretty) const noexcept {
    std::string out;
    
    for (int i = 7; i > -1; --i) {
        out += "----------------------------------\n";
        out += std::to_string(i + 1);
        for (uint8_t j = 0; j < 8; ++j) {
            out += "| ";
            out += _convert_to_char(at(j, i));
            out += " ";
        }

        out += "|";
        out += '\n';
    }
    out += "----------------------------------\n";

    return out;
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
            return Piece::EMPTY;
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
            return ' ';
    }
}

void Board::_parse_FEN(const std::string &FEN) {
    std::istringstream iss(FEN);

    std::string placement, stm, castling, ep;
    int halfmove, fullmove;

    if (!(iss >> placement >> stm >> castling >> ep >> halfmove >> fullmove))
        throw std::runtime_error("Invalid FEN.");

    _board.fill(static_cast<uint8_t>(Piece::EMPTY));

    int rank = 7;   // FEN starts at rank 8
    int file = 0;

    for (char c : placement) {
        if (c == '/') {
            if (file != 8)
                throw std::runtime_error("Invalid FEN row.");

            --rank;
            file = 0;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(c))) {
            file += c - '0';
        } else {
            if (file >= 8 || rank < 0)
                throw std::runtime_error("Invalid FEN placement.");

            _board[_convert_to_1d(file, rank)] =
                static_cast<uint8_t>(_convert_to_piece(c));

            ++file;
        }
    }

    if (rank != 0 || file != 8)
        throw std::runtime_error("Incorrect number of squares.");

    _turn = (stm == "w");

    _castle_rights = {false, false, false, false};
    if (castling != "-") {
        for (char c : castling) {
            switch (c) {
            case 'K': _castle_rights[0] = true; break;
            case 'Q': _castle_rights[1] = true; break;
            case 'k': _castle_rights[2] = true; break;
            case 'q': _castle_rights[3] = true; break;
            default:
                throw std::runtime_error("Invalid castling rights.");
            }
        }
    }

    if (ep == "-") {
        _en_passant = -1; // or std::nullopt
    } else {
        if (ep.size() != 2 ||
            ep[0] < 'a' || ep[0] > 'h' ||
            ep[1] < '1' || ep[1] > '8')
            throw std::runtime_error("Invalid en passant square.");

        int file = ep[0] - 'a';
        int rank = ep[1] - '1';

        // Adjust if your board indexing differs.
        _en_passant = rank * 8 + file;
    }

    _half_clock_move_count = halfmove;
    _move_count = fullmove;
}