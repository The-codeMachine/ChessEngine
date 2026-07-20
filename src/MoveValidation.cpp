#include <MoveValidation.hpp>

namespace Moves
{

    // Checks whether or not you are trying to capture your own piece returns true if you are
    static bool checkIsOwnPiece(Move move, Board board, bool turn)
    {
        // if its white turn then check if it is a white piece
        // if it is not then check if it is a black piece.
        // if the piece coorespondes with the turn then it is
        // invalid.
        return !board.empty(move.second) && isWhite(move.second, board) == turn;
    }

    // Checks if all squares between (x, y) and (xx, yy) are empty. 
    // (x, y) and (xx, yy) are exclusive. 
    static bool isEmptyBetween(Move move, Board &board)
    {
        int dx = move.second.x - move.first.x;
        int dy = move.second.y - move.first.y;

        // determine step direction
        int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
        int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

        // ensures the move is diagonal, horizontal, or vertical
        if (!(dx == 0 || dy == 0 || std::abs(dx) == std::abs(dy)))
            return false;

        move.first.x += stepX;
        move.first.y += stepY;

        while (move.first.x != move.second.x 
            || move.first.y != move.second.y)
        {
            if (!board.empty(move.first))
                return false;

            move.first.x += stepX;
            move.first.y += stepY;
        }

        return true;
    }

    // Checks whether or not a specific piece is white.
    bool isWhite(Position pos, Board &board)
    {
        uint8_t piece = static_cast<uint8_t>(board.at(pos));

        return piece < 7U && piece != 0U;
    }

    // Checks whether or not a specific piece is black.
    bool isBlack(Position pos, Board &board)
    {
        uint8_t piece = static_cast<uint8_t>(board.at(pos)); 

        return piece >= 7U && piece != 0U;
    }

    // Checks whether a pawn can move to a specific square.
    bool movePawn(Move move, Board &board, bool turn)
    {
        // checks rank (based off if its a white or black pawn)
        if (turn ? (move.second.y != move.first.y + 1) 
            : (move.second.y != move.first.y - 1))
            return false;

        // if moving forward, that square must be empty
        if (move.second.x == move.first.x && board.empty(move.second))
            return true;

        // if not moving forward, then must be moving diagonally
        if (move.second.x != move.first.x + 1 
                && move.second.x != move.first.x - 1)
            return false;

        // enpassant location is explicitily trusted to be up-to-date and accurate
        Position enPassantLocation = board.enPassant();
        if (enPassantLocation.x == move.second.x && enPassantLocation.y == move.second.y)
            return true;

        // checks that square is occupied by a black piece
        return turn != isWhite(move.second, board);
    }

    // Checks whether a rook can move to a specific square.
    bool moveRook(Move move, Board &board, bool turn)
    {
        if (checkIsOwnPiece(move, board, turn))
            return false;

        if (!(move.first.x == move.second.x 
            || move.first.y == move.second.y))
            return false;

        return isEmptyBetween(move, board);
    }

    // Checks whether or not a bishop can move to that specific square.
    bool moveBishop(Move move, Board &board, bool turn)
    {
        if (checkIsOwnPiece(move, board, turn))
            return false;

        int xDiff = std::abs(move.second.x - move.first.x);
        int yDiff = std::abs(move.second.y - move.first.y);

        // Must move diagonally.
        if (xDiff != yDiff)
            return false;

        return isEmptyBetween(move, board);
    }

    // Checks whether or not a knight could move to that specific square.
    bool moveKnight(Move move, Board &board, bool turn)
    {
        if (checkIsOwnPiece(move, board, turn))
            return false;

        int xDiff = std::abs(move.first.x - move.second.x);
        int yDiff = std::abs(move.first.y - move.second.y);
        if ((xDiff != 2 && yDiff != 1) && (xDiff != 1 && yDiff != 2))
            return false;

        return true;
    }

    // Checks whether or not a queen can move to that square.
    bool moveQueen(Move move, Board &board, bool turn)
    {
        if (checkIsOwnPiece(move, board, turn))
            return false;

        return isEmptyBetween(move, board);
    }

    // Checks whether or not the king can move to that square.
    bool moveKing(Move move, Board &board, bool turn)
    {
        if (checkIsOwnPiece(move, board, turn))
            return false;

        // castling from board is expected to be up-to-date, and
        // trusted to be accurate (as for as psuedo legal moves go)

        std::array<bool, 4> rights = board.castling();

        // if it is white's turn
        if (turn)
        {
            if (rights[0] && move.second.x == 6 && move.second.y == 0 && isEmptyBetween(move, board))
                return true;
            else if (rights[1] && move.second.x == 2 && move.second.y == 0 && isEmptyBetween(move, board))
                return true;
        }
        else
        {
            if (rights[2] && move.second.x == 6 && move.second.y == 7 && isEmptyBetween(move, board))
                return true;
            else if (rights[3] && move.second.x == 2 && move.second.y == 7 && isEmptyBetween(move, board))
                return true;
        }

        if (std::abs(move.second.x - move.first.x) != 1
         && std::abs(move.second.y - move.first.y) != 1)
            return false;

        return true;
    }

} // namespace Moves