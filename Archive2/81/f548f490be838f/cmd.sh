set -x ; cat main.cpp > main.c
gcc-4.8 -O0 -pedantic -Wall -Wextra -Wconversion -Wshadow -std=c11 -pthread main.c && ./a.out