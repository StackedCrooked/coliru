#!/bin/bash
ulimit -u 20
ulimit -t 20
cd /tmp
rm -f .stdout
export LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"
g++-4.7 -o test -std=c++11 -Wall -Wextra -pedantic-errors -O2 -g -I/usr/include -I/usr/local/include -L/usr/lib -L/usr/local/lib main.cpp -pthread -lPocoFoundation -ltbb -lboost_thread -lboost_system && ./test >.stdout
[ ! -f .stdout ] || cat .stdout
