set -x; gcc -x c -std=c99 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang -x c  -std=c99 -O2 -Wall -pedantic -pthread main.cpp && ./a.out