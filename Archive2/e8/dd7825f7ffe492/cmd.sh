clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++
./a.out <<< '1 2 3 4 5 4 3 2 1 .'
./a.out <<< '1 2 3 4 5 5 4 3 2 1 .'
./a.out <<< '1 2 3 4 5 5 3 2 1 .'