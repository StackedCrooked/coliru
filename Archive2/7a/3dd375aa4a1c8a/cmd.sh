clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && ./a.out& for a in {1..10}; do netcat 127.0.0.1 6767& done | uniq -c