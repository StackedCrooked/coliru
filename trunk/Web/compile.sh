#!/bin/bash
ulimit -u 20
ulimit -t 5
cd /tmp
g++-4.7 -o test -std=c++0x -Wall -Werror -Wextra -pedantic-errors -O2 -I/usr/include -I/usr/include -L/usr/lib -pthread main.cpp && ./test
