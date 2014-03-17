ln -s main.cpp main.c
echo '------------------- hosted -------------------------------'
clang -std=c11 -Wall -Wextra -pedantic-errors -c main.c && echo '*** ok ***' || echo '*** error ***'
gcc-4.8 -std=c11 -Wall -Wextra -pedantic-errors -c main.c && echo '*** ok ***' || echo '*** error ***'
echo '------------------- freestanding --------------------------'
clang -std=c11 -Wall -Wextra -pedantic-errors -ffreestanding -c main.c && echo '*** ok ***' || echo '*** error ***'
gcc-4.8 -std=c11 -Wall -Wextra -pedantic-errors -ffreestanding -c main.c && echo '*** ok ***' || echo '*** error ***'