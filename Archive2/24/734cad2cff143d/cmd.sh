set -x ;
clang++ -O3 -pedantic -Wall -Wextra -Wconversion -std=c++03 -pthread main.cpp && ./a.out