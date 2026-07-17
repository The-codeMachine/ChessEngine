#include "../include/MoveCalculation.hpp"

namespace Moves {

    bool isWhite(int x, int y, Board& board) {
        uint8_t piece = static_cast<uint8_t>(board.at(x, y));

        return piece < 7U && piece != 0U;
    }

    bool isBlack(int x, int y, Board& board) {
        uint8_t piece = static_cast<uint8_t>(board.at(x, y));

        return piece >= 7U && piece != 0U;
    }

    bool movePawn(int x, int y, int xx, int yy, Board& board, bool turn) {
        // checks rank (based off if its a white or black pawn)
        if (turn ? (yy != y + 1) : (yy != y - 1))
            return false;

        // if moving forward, that square must be empty
        if (xx == x && board.empty(xx, yy))
            return true;
        
        // if not moving forward, then must be moving diagonally
        if (xx != x + 1 && xx != x - 1)
            return false;

        // checks that square is occupied by a black piece
        return turn != isWhite(xx, yy, board);
    }

    bool moveRook(int x, int y, int xx, int yy, Board& board, bool turn) {
        // if its white turn then check if it is a white piece
        // if it is not then check if it is a black piece.
        // if the piece coorespondes with the turn then it is
        // invalid.
        if (!board.empty(xx, yy) && isWhite(xx, yy, board) == turn)
            return false;

        // if it is moving along a file check all pieces on that file
        if (x == xx) {
            for (int i = std::min(y, yy); i < std::max(y, yy); ++i) {
                if (!board.empty(x, i))
                    return false;
            }

        // if it is moving along a rank, check all pieces on that rank
        } else if (y == yy) {
            for (int i = std::min(x, xx); i < std::max(x, xx); ++i) {
                if (!board.empty(i, y))
                    return false;
            }
        }

        return true;
    }

    bool moveBishop(int x, int y, int xx, int yy, Board& board, bool turn) {
        // Cannot capture your own piece.
        if (!board.empty(xx, yy) && isWhite(xx, yy, board) == turn)
            return false;

        int xDiff = std::abs(xx - x);
        int yDiff = std::abs(yy - y);

        // Must move diagonally.
        if (xDiff != yDiff)
            return false;

        int dx = (xx > x) ? 1 : -1;
        int dy = (yy > y) ? 1 : -1;

        int cx = x + dx;
        int cy = y + dy;

        // Check every square between the start and destination.
        while (cx != xx && cy != yy) {
            if (!board.empty(cx, cy))
                return false;

            cx += dx;
            cy += dy;
        }

        return true;
    }

    bool moveKnight(int x, int y, int xx, int yy, Board& board, bool turn) {
        // if its white turn then check if it is a white piece
        // if it is not then check if it is a black piece.
        // if the piece coorespondes with the turn then it is
        // invalid.
        if (!board.empty(xx, yy) && isWhite(xx, yy, board) == turn)
            return false;

        int xDiff = std::abs(x - xx);
        int yDiff = std::abs(y - yy);
        if ((xDiff != 2 && yDiff != 1) && (xDiff != 1 && yDiff != 2))
            return false;

        return true;
    }

    bool moveQueen(int x, int y, int xx, int yy, Board& board, bool turn) {
        if (!board.empty(xx, yy) && isWhite(xx, yy, board) == turn)
            return false;

        return moveRook(x, y, xx, yy, board, turn) || moveBishop(x, y, xx, yy, board, turn);
    }

    bool moveKing(int x, int y, int xx, int yy, Board& board, bool turn) {
        if (!board.empty(xx, yy) && isWhite(xx, yy, board) == turn)
            return false;

        if (std::abs(xx - x) != 1 && std::abs(yy - y) != 1)
            return false;

        return true;
    }

} // namespace Moves