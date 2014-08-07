time od -Anone -w4 -t u2 -v /dev/urandom | head -n 4000 > pairs.txt; 
g++ -std=c++11 -Os -Wall -pedantic main.cpp && ./a.out