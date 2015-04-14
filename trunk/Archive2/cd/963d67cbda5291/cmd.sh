mkdir -p haystack/{a..z}/sub/{1..10} haystack/j/sub/9/needle
g++ -std=c++03 -O2 -Wall -pedantic -pthread main.cpp -lboost_system -lboost_filesystem -o test
cd haystack/k/sub/4 && ../../../../test