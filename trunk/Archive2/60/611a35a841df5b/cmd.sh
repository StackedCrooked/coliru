set -x;
clang++ -O0 -Wall -Wextra -Wconversion -pedantic -Wno-unused-variable -Wno-unused-parameter -std=c++1y -pthread main.cpp && ./a.out