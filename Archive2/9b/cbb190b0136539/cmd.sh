clang++ -std=c++11 -Os -Wall -pthread -pedantic main.cpp -lboost_system -lboost_program_options
./a.out -O23
./a.out -O 4
./a.out -I /usr/include -I /usr/local/include
./a.out --optimization=3