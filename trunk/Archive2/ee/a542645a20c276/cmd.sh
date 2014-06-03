set -x;
clang++ -std=c++11 -O2 -Wall -Wno-unused-variable -pthread main.cpp && ./a.out
g++-4.8 -std=c++11 -O2 -Wall -Wno-unused-variable -pthread main.cpp && ./a.out