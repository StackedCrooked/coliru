title Exercise 1 fail
g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | column -t | sort -R | head -n20 | sort -n