#title checksum routine generates instruction-cache misses (according to cachegrind)
g++-4.7 -std=c++11 -c -O2 -Wall -pedantic -pthread main.cpp -S -masm=intel -o -