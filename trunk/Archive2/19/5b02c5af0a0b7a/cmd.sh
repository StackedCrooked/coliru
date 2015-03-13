#title Circular allocator for dispatcher (producer/consumer allocator)
g++ -std=c++11  -O2 -Wall -pedantic -pthread -lboost_system -lboost_thread main.cpp && ./a.out