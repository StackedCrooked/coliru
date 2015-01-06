ln -s main.cpp main.c
clang -std=c89 -O2 -Wall -Wextra -pedantic-errors -c main.c && echo 'clang c89 allows void main()'
gcc -std=c89 -O2 -Wall -Wextra -pedantic-errors -c main.c && echo 'gcc c89 allows void main()'