#title boost coroutine experiment (trying to find a useful application)
g++-4.9 -std=c++14 -O2 -Wall -pedantic -pthread main.cpp -lboost_system -lboost_coroutine -lboost_context && ./a.out