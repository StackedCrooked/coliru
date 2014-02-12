ln -s main.cpp main.c
gcc -std=c99 -Wall -Wextra -pedantic-errors -O2 main.c && ./a.out <<< 'how now brown cow'