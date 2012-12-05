#!/bin/bash
ulimit -u 20
ulimit -t 10
cd /tmp
rm -f .stdout
g++-4.7 -o test -std=c++0x -Wall -Wextra -pedantic-errors -I/usr/include -I/usr/local/include -L/usr/lib -L/usr/local -pthread main.cpp && ./test >.stdout
[ ! -f .stdout ] || cat .stdout
