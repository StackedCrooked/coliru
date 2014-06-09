ln -s main.cpp main.c && clang -std=c99 -O2 -Wall -Wextra -pedantic-errors main.c && ./a.out
echo '-------- now try assigning to arg ----------'
clang -DTRY_ASSIGNMENT -std=c99 -O2 -Wall -Wextra -pedantic-errors main.c && ./a.out