clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo 'log.txt contains:' && cat log.txt