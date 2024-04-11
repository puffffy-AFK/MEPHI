cmake_minimum_required(VERSION 3.19)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(alphabet AlphabetPointer.cpp)
add_executable(histogram Histogram.cpp)
add_executable(tic_tac_toe TicTacToe.cpp)