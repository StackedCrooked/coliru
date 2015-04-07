clang++ -std=c++11 -Os -Wall -pthread -pedantic main.cpp -lboost_system -lboost_thread && ./a.out& 
for a in S{a..d}\ $RANDOM Gnonexisting L; do echo "$a -> $(nc 127.0.0.1 5001 <<< "$a")"; done | nl