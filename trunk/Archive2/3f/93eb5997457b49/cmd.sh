set -x ; g++-4.8 -pthread -std=c++11 -O2 -Wall -pedantic main.cpp -lboost_thread -lboost_system && ./a.out