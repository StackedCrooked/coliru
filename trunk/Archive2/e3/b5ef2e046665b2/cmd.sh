set -x ; 
g++-4.8 -std=c++11 -O0 -Wall -pedantic -Wextra -pthread main.cpp -lboost_regex && ./a.out