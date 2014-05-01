set -x;
clang++ -O0 -Wall -pedantic -Wextra -Wconversion -pthread -std=c++1y main.cpp && ./a.out