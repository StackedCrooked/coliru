set -x
g++-4.8 -O3 -Wall -Wextra -pedantic -std=c++11 -Wconversion -pthread main.cpp && ./a.out