#!/bin/bash
ulimit -u 20
ulimit -t 20
cd /tmp
rm -f .stdout
g++-4.7 -o test -std=c++11 -Wall -Wextra -pedantic-errors -Wno-unused-variable -O2 -g3 -I/usr/include -I/usr/local/include -L/usr/lib -L/usr/local main.cpp -pthread -lPocoFoundation -ltbb && time ./test >.stdout
[ ! -f .stdout ] || cat .stdout
