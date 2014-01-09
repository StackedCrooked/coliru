set -x
clang++ -O3 -pedantic -Wall -Wextra -Wconversion -std=c++11 -pthread main.cpp && ./a.out