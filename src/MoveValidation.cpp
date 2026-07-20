#include <MoveValidation.hpp>

namespace Moves
{

    // Checks whether or not a specific piece is white.
    static bool isWhite(int x, int y, Board &board)
    {
        uint8_t piece = static_cast<uint8_t>(board.at(x, y));

        return piece < 7U && piece != 0U;
    }

    // Checks whether or not a specific piece is black.
    static bool isBlack(int x, int y, Board &board)
    {
        uint8_t piece = static_cast<uint8_t>(board.at(x, y));

        return piece >= 7U && piece != 0U;
    }

    // Checks whether or not you are trying to capture your own piece returns true if you are
    static bool checkIsOwnPiece(int x, int y, int xx, int yy, Board board, bool turn)
    {
        // if its white turn then check if it is a white piece
        // if it is not then check if it is a black piece.
        // if the piece coorespondes with the turn then it is
        // invalid.
        return !board.empty(xx, yy) && isWhite(xx, yy, board) == turn;
    }

    // Checks if all squares between (x, y) and (xx, yy) are empty. 
    // (x, y) and (xx, yy) are exclusive. 
    static bool isEmptyBetween(int x, int y, int xx, int yy, Board &board)
    {
        int dx = xx - x;
        int dy = yy - y;

        // determine step direction
        int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
        int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

        // ensures the move is diagonal, horizontal, or vertical
        if (!(dx == 0 || dy == 0 || std::abs(dx) == std::abs(dy)))
            return false;

        x += stepX;
        y += stepY;

        while (x != xx || y != yy)
        {
            if (!board.empty(x, y))
                return false;

            x += stepX;
            y += stepY;
        }

        return true;
    }

    // Checks whether a pawn can move to a specific square.
    bool movePawn(int x, int y, int xx, int yy, Board &board, bool turn)
    {
        // checks rank (based off if its a white or black pawn)
        if (turn ? (yy != y + 1) : (yy != y - 1))
            return false;

        // if moving forward, that square must be empty
        if (xx == x && board.empty(xx, yy))
            return true;

        // if not moving forward, then must be moving diagonally
        if (xx != x + 1 && xx != x - 1)
            return false;

        // enpassant location is explicitily trusted to be up-to-date and accurate
        Position enPassantLocation = board.enPassant();
        if (enPassantLocation.first == xx && enPassantLocation.second == yy)
            return true;

        // checks that square is occupied by a black piece
        return turn != isWhite(xx, yy, board);
    }

    // Checks whether a rook can move to a specific square.
    bool moveRook(int x, int y, int xx, int yy, Board &board, bool turn)
    {
        if (checkIsOwnPiece(x, y, xx, yy, board, turn))
            return false;

        if (!(x == xx || y == yy))
            return false;

        return isEmptyBetween(x, y, xx, yy, board);
    }

    // Checks whether or not a bishop can move to that specific square.
    bool moveBishop(int x, int y, int xx, int yy, Board &board, bool turn)
    {
        if (checkIsOwnPiece(x, y, xx, yy, board, turn))
            return false;

        int xDiff = std::abs(xx - x);
        int yDiff = std::abs(yy - y);

        // Must move diagonally.
        if (xDiff != yDiff)
            return false;

        return isEmptyBetween(x, y, xx, yy, board);
    }

    // Checks whether or not a knight could move to that specific square.
    bool moveKnight(int x, int y, int xx, int yy, Board &board, bool turn)
    {
        if (checkIsOwnPiece(x, y, xx, yy, board, turn))
            return false;

        int xDiff = std::abs(x - xx);
        int yDiff = std::abs(y - yy);
        if ((xDiff != 2 && yDiff != 1) && (xDiff != 1 && yDiff != 2))
            return false;

        return true;
    }

    // Checks whether or not a queen can move to that square.
    bool moveQueen(int x, int y, int xx, int yy, Board &board, bool turn)
    {
        if (checkIsOwnPiece(x, y, xx, yy, board, turn))
            return false;

        return isEmptyBetween(x, y, xx, yy, board);
    }

    // Checks whether or not the king can move to that square.
    bool moveKing(int x, int y, int xx, int yy, Board &board, bool turn)
    {
        if (checkIsOwnPiece(x, y, xx, yy, board, turn))
            return false;

        // castling from board is expected to be up-to-date, and
        // trusted to be accurate (as for as psuedo legal moves go)

        std::array<bool, 4> rights = board.castling();

        // if it is white's turn
        if (turn)
        {
            if (rights[0] && xx == 6 && yy == 0 && isEmptyBetween(x, y, xx, yy, board))
                return true;
            else if (rights[1] && xx == 2 && yy == 0 && isEmptyBetween(x, y, xx, yy, board))
                return true;
        }
        else
        {
            if (rights[2] && xx == 6 && yy == 7 && isEmptyBetween(x, y, xx, yy, board))
                return true;
            else if (rights[3] && xx == 2 && yy == 7 && isEmptyBetween(x, y, xx, yy, board))
                return true;
        }

        if (std::abs(xx - x) != 1 && std::abs(yy - y) != 1)
            return false;

        return true;
    }

} // namespace Moves