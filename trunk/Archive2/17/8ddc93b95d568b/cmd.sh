while sleep 1; do date; done | nc -l 6767& 
clang++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp -lboost_system &&
./a.out