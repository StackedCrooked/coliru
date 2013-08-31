g++-4.8 -std=c++11 -O3 -pthread main.cpp
strace ./a.out | c++filt