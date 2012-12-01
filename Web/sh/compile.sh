#!/bin/bash
ulimit -u 20
ulimit -t 5
cd /tmp
rm -f .stdout
g++-4.7 -o test -std=c++0x -Wall -Werror -Wextra -pedantic-errors -Wno-unused-variable -O2 -I/usr/include -I/usr/local/include -L/usr/lib -L/usr/local -pthread main.cpp && ./test >.stdout
[ ! -f .stdout ] || cat .stdout
