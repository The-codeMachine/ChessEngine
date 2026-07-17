#include "Board.hpp"

namespace Moves {

    bool movePawn(int x, int y, int xx, int yy, Board& board, bool turn);

    bool moveRook(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveBishop(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveKnight(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveQueen(int x, int y, int xx, int yy, Board& board, bool turn);
    bool moveKing(int x, int y, int xx, int yy, Board& board, bool turn);

} // namespace Moves