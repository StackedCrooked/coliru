echo g++
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo clang
clang++ -std=c++11 main.cpp -pedantic && ./a.out