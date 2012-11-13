#!/bin/sh
ccache g++-4.7 -o main.o -Wall -Werror -Wextra -pedantic-errors -std=c++0x -pthread -I/usr/local/include main.cpp
