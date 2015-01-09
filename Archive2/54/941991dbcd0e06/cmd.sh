#ThreadLocal<T> (substitute for thread_local in older compilers)
g++-4.7 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -lboost_thread && ./a.out