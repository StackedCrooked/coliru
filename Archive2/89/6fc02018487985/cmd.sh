set -x
g++-4.8 -O3 -pedantic -Wall -Wextra -Wconversion -std=c++11 -pthread main.cpp && ./a.out