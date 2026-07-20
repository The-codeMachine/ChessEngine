#include <MoveCalculation.hpp>

#include <MoveValidation.hpp>

namespace Moves {

    // Generates all pseudo legal moves for a board
    std::vector<Move> generatePseudoLegalMoves(Board& board, bool turn) {

    }
    
    // Generates all legal moves for a board
    std::vector<Move> generateLegalMoves(Board& board, bool turn) {

    }

    // Generates all pseudo legal moves for a piece
    std::vector<Move> generatePseudoLegalMoves(Position piece, Board& board, bool turn) {
        if (board.empty(piece) || isWhite(piece, board) != turn)
            return {};

        
    }
    
    // Generates all legal moves for a piece
    std::vector<Move> generateLegalMove(Position piece, Board& board, bool turn) {

    }

} // namespace Moves