ln -s main.cpp main.c
gcc -std=c89 -O2 -Wall -pedantic -pthread main.c && ./a.out