od -Anone -w8 -t f8 /dev/urandom | head -10 | sort -g > floats;
od -Anone -w4 -t u4 /dev/urandom | head -10 > uints;
paste floats uints > input.txt;
g++ -std=c++11 -O3 -march=native -Wall -pedantic -pthread main.cpp -lboost_system -lboost_iostreams && ./a.out