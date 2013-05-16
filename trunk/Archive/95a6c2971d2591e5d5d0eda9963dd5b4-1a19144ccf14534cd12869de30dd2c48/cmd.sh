set -x
ulimit -u 20
g++ -std=c++11 -O2 -pthread main.cpp && ./a.out