set -x;
g++-4.8 -O0 -Wall -pedantic -Wextra -pthread -std=c++1y main.cpp -lboost_system && ./a.out