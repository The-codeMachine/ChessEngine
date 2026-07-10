#include "Piece.hpp"

class Pawn : Piece
{
public:
    Pawn(int x, int y, bool white) :
        Piece(x, y, white, 1) {}

    bool move(int x, int y);
    std::vector<int> calculateValidMoves(const Board& board) const noexcept;

};