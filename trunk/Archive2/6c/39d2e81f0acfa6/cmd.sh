set -x ;
clang++ -O3 -pedantic -Wall -Wextra -Wconversion -Wshadow -std=c++1y -pthread main.cpp && ./a.out