ln -s main.cpp main.c
gcc -std=c99 -Wall -Wextra -pedantic-errors -O3 main.c && ./a.out <<< 123456789