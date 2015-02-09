g++ --version | head -n 1
clang++ --version | head -n 1
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out