#title reconstructor on self (stack upgrading)
g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | c++filt