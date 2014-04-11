cat <<HERE > apples_oranges.cfg; clang++ -std=c++11 -O0 -g -Wall -pedantic -pthread main.cpp -lboost_system -lboost_program_options && time ./a.out --name myname -o 800
apple=10
oranges=20
name=heraklites
HERE