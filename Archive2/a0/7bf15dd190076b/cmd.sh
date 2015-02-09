while sleep 1; do date; done | nc -l 6768& 
clang++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp -lboost_system &&
./a.out