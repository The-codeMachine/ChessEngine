#pragma once

#include <Board.hpp>

#include <vector>

/*
This consists of calculation for all valid, legal 
moves within a single board. Based off a board it
can generate all valid moves. This includes which
specific piece to calculate, or all pieces. 
Exact operations include:
 - Generate all pseudo legal moves
 - Generate all legal moves
 - Generate all pseudo legal moves of a specific piece 
    (e.g. a specific knight, or queen)
 - Generate all legal moves of a specific piece (e.g king,
    or rook)

*/


namespace Moves {

    std::vector<Move> generatePseudoLegalMoves(Board& board, bool turn);
    std::vector<Move> generateLegalMoves(Board& board, bool turn);

    std::vector<Move> generatePseudoLegalMoves(Position piece, Board& board, bool turn);
    std::vector<Move> generateLegalMove(Position piece, Board& board, bool turn);

} // namespace Moves