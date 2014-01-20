g++-4.8 -S -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && grep 120 main.s;
g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out;