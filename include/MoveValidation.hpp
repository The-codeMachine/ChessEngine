#include <Board.hpp>

/*
Move validation consists of generating psuedo-legal
moves for each piece. This does not check whether the
king is in check, if a piece is pinned, etc. However,
this will verify whether a piece is:
 - Eligible for en passant
 - Eligible for castling (both sides)
 - Able to capture
 - Able to move to that specific square based off their movement rules

Currently, the functions only consist of checking one 
specific move. Move calculation functions can be found
within the MoveCalculation.hpp file. 

*/

namespace Moves {

    bool movePawn(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveRook(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveBishop(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveKnight(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveQueen(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveKing(int x, int y, int xx, int yy, Board& board, bool turn);

} // namespace Moves