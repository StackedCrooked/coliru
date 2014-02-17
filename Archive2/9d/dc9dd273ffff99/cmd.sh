set -x
g++-4.8 -std=c++11 -O2 -Wall -pedantic -Wextra -pthread -lboost_regex -lboost_system main.cpp && ./a.out