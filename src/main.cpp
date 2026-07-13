#include "../include/Board.hpp"

#include <stdexcept>
#include <iostream>

int main() {

    try {
    Board b("4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1");
    std::cout << b.toString(true) << "\n";
    } catch (const std::exception& e) {
        std::cout << "idk: " << e.what() << "\n";
    }

    return 0;
}