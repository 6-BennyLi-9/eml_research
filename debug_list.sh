#! /bin/bash

g++-${{ matrix.gcc }} -std=c++20 main.cpp -o main
g++-${{ matrix.gcc }} -std=c++20 bin_depth.cpp -o bin_depth

./main --mode 0
./main --mode 5
./bin_depth
