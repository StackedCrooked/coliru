#!/bin/bash
ulimit -u 20
ulimit -t 20
cd /tmp
rm -f .stdout
time g++-4.7 -o test -std=c++0x -Wall -Wextra -pedantic-errors -Wno-unused-variable -O2 -g3 -I/usr/include -I/usr/local/include -L/usr/lib -L/usr/local main.cpp -pthread -lPocoFoundation -ltbb && ./test >.stdout
[ ! -f .stdout ] || cat .stdout
