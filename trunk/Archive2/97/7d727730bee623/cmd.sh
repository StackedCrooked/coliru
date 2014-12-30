clang++ -std=c++11 -O2 -Wall -pthread main.cpp -lboost_system -lboost_thread
time (./a.out& (for a in {1..4}; do nc 127.0.0.1 6767& done | nl&); sleep 2; killall nc; wait)