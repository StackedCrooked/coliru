set -x ; 
clang++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -lboost_system main.cpp && ./a.out