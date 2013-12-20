set -x
clang++ -O3 -Wall -Wextra -pedantic -std=c++11 -Wconversion -pthread main.cpp && ./a.out