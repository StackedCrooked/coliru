ln -s main.cpp main.c
echo 'clang c99' && clang -std=c99 -O2 -Wall -Wextra -pedantic-errors main.c && ./a.out <<< -1
echo -e '\ngcc c99' && gcc -std=c99 -O2 -Wall -Wextra -pedantic-errors main.c && ./a.out <<< -1