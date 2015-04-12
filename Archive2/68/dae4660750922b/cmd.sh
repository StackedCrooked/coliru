clang++ -std=c++11 -Os -Wall -pedantic main.cpp -o use-boost.o -c
clang++ -std=c++11 -Os -Wall -pedantic main.cpp -o use_std.o -c -DUSE_STD