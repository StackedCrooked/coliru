set -x;
g++-4.8 -O0 -Wall -pedantic -Wextra -Wconversion -pthread -fno-builtin -std=c++1y main.cpp && ./a.out