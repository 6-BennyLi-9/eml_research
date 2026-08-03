#! /bin/bash set -euo pipefail

gcc main.cpp -std=c++20 -O2 -Wall -Wextra -o main
gcc bin_depth.cpp -std=c++20 -O2 -Wall -Wextra -o bin_depth

ls -la

./main --mode 0
./main --mode 5
./bin_depth
