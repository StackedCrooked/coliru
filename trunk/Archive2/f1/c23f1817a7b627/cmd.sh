clang++ -std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ 
./a.out 5000000 && ./a.out 25000000 && ./a.out 100000000 && ./a.out 200000000