clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp
od -A none -t o /dev/urandom | tr -cd '01' | dd bs=1 count=4096 | ./a.out