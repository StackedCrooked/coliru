cat<<INPUT >input.txt; clang++ -std=c++11 -Os -Wall -pedantic main.cpp -lboost_system && ./a.out
#include <WinUser32.mqh>

void foo(int bar, double baz) { int lol = 0; }
INPUT