g++ -std=c++11 -Os -Wall -pthread main.cpp -lboost_system -lboost_thread && ./a.out & for a in {1..8}; do yes | netcat -u 127.0.0.1 1313  & done | uniq -c