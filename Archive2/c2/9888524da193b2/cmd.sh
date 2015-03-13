#title Page allocator for dispatcher (producer/consumer allocator)
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic -pthread -lboost_system main.cpp && ./a.out