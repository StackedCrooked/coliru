g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp
./a.out && ./a.out -t 2 && ./a.out -n there && ./a.out -t 3 -n again && ./a.out -n hello -t 2