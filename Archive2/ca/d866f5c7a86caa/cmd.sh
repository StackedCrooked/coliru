clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++
./a.out 8 ASCENDING
./a.out 5 DESCENDING
./a.out 7 RANDOM
./a.out 6 EQUAL
./a.out 12 EQUAL 12345