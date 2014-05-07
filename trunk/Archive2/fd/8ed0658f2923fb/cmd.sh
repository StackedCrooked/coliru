g++ -std=c++11 -O2 -Wall -pedantic main.cpp
LD_PRELOAD=./libmalloc_hook.so strace ./a.out