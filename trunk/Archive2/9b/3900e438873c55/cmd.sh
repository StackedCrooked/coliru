test() { echo "$1: $($1 -std=c++1y -O2 -Wall -pedantic -pthread main.cpp && ./a.out)" ; }
test g++
test clang++