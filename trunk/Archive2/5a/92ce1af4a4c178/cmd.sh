set -x; mv main.cpp main.c ; gcc -std=c99 -O0 -Wall -Wextra -pedantic -pthread main.c && ./a.out abc
clang -std=c99 -O0 -Wall -pedantic -pthread main.c  && ./a.out abc