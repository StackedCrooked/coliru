set -x; clang++ -std=c++11 -march=native -Wall -Wextra -pedantic -pthread main.cpp -lsupc++ -g && ./a.out