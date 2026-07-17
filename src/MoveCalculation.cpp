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

    bool moveWhitePawn(int x, int y, int xx, int yy, Board& board) {
        // checks rank
        if (yy != y + 1)
            return false;

        // if moving forward, that square must be empty
        if (xx == x && board.empty(xx, yy))
            return true;
        
        // if not moving forward, then must be moving diagonally
        if (xx != x + 1 && xx != x - 1)
            return false;

        // checks that square is occupied by a black piece
        return isBlack(xx, yy, board);
    }

    bool moveBlackPawn(int x, int y, int xx, int yy, Board& board) {
        // checks rank 
        if (yy != y - 1)
            return false;

        // if moving forward then square must be empty
        if (xx == x && board.empty(xx, yy))
            return true;
        
        // if not moving forward, must be moving diagonally
        if (xx != x + 1 && xx != x - 1)
            return false;

        // checks that the square is occupied by a white piece
        return isWhite(xx, yy, board);
    }

    bool moveRook(int x, int y, int xx, int yy, Board& board, bool turn) {
        // if its white turn then check if it is a white piece
        // if it is not then check if it is a black piece.
        // if the piece coorespondes with the turn then it is
        // invalid.
        if (isWhite(xx, yy, board) == turn)
            return false;

        // if it is moving along a file check all pieces on that file
        if (x == xx) {
            for (int i = y; i < yy; ++i) {
                if (!board.empty(x, i))
                    return false;
            }

        // if it is moving along a rank, check all pieces on that rank
        } else if (y == yy) {
            for (int i = x; i < xx; ++i) {
                if (!board.empty(i, y))
                    return false;
            }
        }

        return true;
    }

    bool moveBishop(int x, int y, int xx, int yy, Board& board, bool turn) {
        if (isWhite(xx, yy, board) == true)
            return false;
    }

    bool moveKnight(int x, int y, int xx, int yy, Board& board, bool turn) {
        // if its white turn then check if it is a white piece
        // if it is not then check if it is a black piece.
        // if the piece coorespondes with the turn then it is
        // invalid.
        if (isWhite(xx, yy, board) == turn)
            return false;

        int xDiff = std::abs(x - xx);
        int yDiff = std::abs(y - yy);
        if ((xDiff != 2 && yDiff != 1) && (xDiff != 1 && yDiff != 2))
            return false;

        return true;
    }

    bool moveQueen(int x, int y, int xx, int yy, Board& board, bool turn) {
        if (isWhite(xx, yy, board) == true)
            return false;
    }

    bool moveKing(int x, int y, int xx, int yy, Board& board, bool turn) {
        if (isWhite(xx, yy, board) == true)
            return false;
    }



} // namespace Moves