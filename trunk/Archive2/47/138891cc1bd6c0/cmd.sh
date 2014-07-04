title runtime to compile-time bridge
g++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp -S -o - | c++filt