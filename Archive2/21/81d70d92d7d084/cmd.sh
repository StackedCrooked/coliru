set -x; gcc -x c -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang -x c -O2 -Wall -pedantic -pthread main.cpp && ./a.out