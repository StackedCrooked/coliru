ln -sfv /Archive2/9f/8100ce77e42a38/main.cpp input.dot
clang++ -std=c++11 -Os -Wall -pedantic -pthread -lboost_regex main.cpp && ./a.out