set -x
ulimit -u 20
set -x
ulimit -u 20
g++-4.8 -std=c++11 -O2 -pthread main.cpp && ./a.out