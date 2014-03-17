ln -s main.cpp main.c
echo '------------------- freestanding --------------------------'
clang -std=c11 -Wall -Wextra -pedantic-errors -ffreestanding -c main.c && echo '*** ok ***' || echo '*** error ***'
gcc-4.8 -std=c11 -Wall -Wextra -pedantic-errors -ffreestanding -c main.c && echo '*** ok ***' || echo '*** error ***'