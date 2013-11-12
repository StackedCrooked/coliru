set -x
g++ -std=c++11 -g -o main -O3 -Wall -pedantic -pthread main.cpp
objdump -d -j .text main