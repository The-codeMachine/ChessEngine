#include "../include/Board.hpp"

#include <stdexcept>
#include <iostream>

int main() {

    try {
        Board b("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
        
        std::cout << b.toString(true) << "\n";
        std::cout << b.toString(false) << "\n";
    }
    catch (const std::exception &e) {
        std::cout << "idk: " << e.what() << "\n";
    }

    return 0;
}