ln -s main.cpp main.c
clang -std=c90 -O2 -Wall -Wextra -pedantic-errors -c main.c && echo 'clang c90 allows void main()'
gcc -std=c90 -O2 -Wall -Wextra -pedantic-errors -c main.c && echo 'gcc c90 allows void main()'