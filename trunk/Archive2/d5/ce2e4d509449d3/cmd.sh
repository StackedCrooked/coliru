set -x;
g++-4.8 -O0 -Wall -Wextra -Wconversion -pedantic -Wno-unused-variable -Wno-unused-parameter -std=c++11 -pthread main.cpp && ./a.out