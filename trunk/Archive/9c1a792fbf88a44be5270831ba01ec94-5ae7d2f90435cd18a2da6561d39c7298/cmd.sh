g++ -std=c++11 -Wall -Wextra -Werror -pedantic-errors main.cpp -ggdb3 -ltbb && ./a.out
valgrind ./a.out
gdb --eval-command=r ./a.out