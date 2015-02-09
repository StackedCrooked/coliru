while sleep 1; do date; done | head -5 | nc -l 6769& 
clang++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp -lboost_system &&
./a.out