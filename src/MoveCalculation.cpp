#include "../include/MoveCalculation.hpp"

namespace Moves {

    bool moveWhitePawn(int x, int y, int xx, int yy, Board& board) {
        if (yy != y + 1)
            return false;

        if (xx == x && board.empty(xx, yy))
            return true;
        
        if (xx != x + 1 && xx != x - 1)
            return false;

        uint8_t piece = static_cast<uint8_t>(board.at(xx, yy));
        if (piece < 7U && piece > 0U)
            return false;

        return true;
    }

    bool moveBlackPawn(int x, int y, int xx, int yy, Board& board) {
        if (yy != y - 1)
            return false;

        if (xx == x && board.empty(xx, yy))
            return true;
        
        if (xx != x + 1 && xx != x - 1)
            return false;

        uint8_t piece = static_cast<uint8_t>(board.at(xx, yy));
        if (piece >= 7U)
            return false;

        return true;
    }

    bool moveRook(int x, int y, int xx, int yy, Board& board, bool turn) {
        uint8_t piece = static_cast<uint8_t>(board.at(xx, yy));
        if (turn ? (piece < 7U && piece > 0U) 
            : (piece > 7U))
            return false;

        if (x == xx) {
            for (int i = y; i < yy; ++i) {
                if (!board.empty(x, i))
                    return false;
            }
        } else if (y == yy) {
            for (int i = x; i < xx; ++i) {
                if (!board.empty(i, y))
                    return false;
            }
        }

        return true;
    }

    bool moveBishop(int x, int y, int xx, int yy, Board& board, bool turn) {
        uint8_t piece = static_cast<uint8_t>(board.at(xx, yy));
        if (turn ? (piece < 7U && piece > 0U) 
            : (piece > 7U))
            return false;
    }

    bool moveKnight(int x, int y, int xx, int yy, Board& board, bool turn) {
        uint8_t piece = static_cast<uint8_t>(board.at(xx, yy));
        if (turn ? (piece < 7U && piece > 0U) 
            : (piece > 7U))
            return false;

        int xDiff = std::abs(x - xx);
        int yDiff = std::abs(y - yy);
        if ((xDiff != 2 && yDiff != 1) || (xDiff != 1 && yDiff != 2))
            return false;

        return true;
    }

    bool moveQueen(int x, int y, int xx, int yy, Board& board, bool turn) {
        uint8_t piece = static_cast<uint8_t>(board.at(xx, yy));
        if (turn ? (piece < 7U && piece > 0U) 
            : (piece > 7U))
            return false;
    }

    bool moveKing(int x, int y, int xx, int yy, Board& board, bool turn) {
        uint8_t piece = static_cast<uint8_t>(board.at(xx, yy));
        if (turn ? (piece < 7U && piece > 0U) 
            : (piece > 7U))
            return false;
    }



} // namespace Moves