clang++ -std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++
./a.out <<< '( sqrt( 23 + ceil( 22.4 + 54.6 ) ) * 10 ) + 234.56 / 10'