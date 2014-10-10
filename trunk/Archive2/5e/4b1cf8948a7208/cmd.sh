ln -s main.cpp main.c
gcc -std=c99 -O2 -Wall -Wextra -pedantic-errors -Werror -c main.c && echo ok