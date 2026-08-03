#! /bin/bash

gcc main.cpp -std=c++20 -o main
gcc bin_depth.cpp -std=c++20 -o bin_depth

ls

/main --mode 0
/main --mode 5
/bin_depth
