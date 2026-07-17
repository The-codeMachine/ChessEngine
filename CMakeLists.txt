cmake_minimum_required(VERSION 3.25)

project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ChessEngine 
    src/main.cpp 
    src/Board.cpp
    src/MoveCalculation.cpp
)