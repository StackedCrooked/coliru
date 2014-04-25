clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ 
./a.out <<< 123456789 && ./a.out <<< 12345 && ./a.out <<< 123456 && ./a.out <<< abcdefg