title Compile-time determination of the required number of bits to represent an unsigned integer
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | column -t | sed -e 's,_, ,g'