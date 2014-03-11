set -x;
cat main.cpp > main.c
clang -O2 -Wall -pedantic -pthread main.c && ./a.out