clang --version
clang -x c -Wall -Wextra -Werror -pedantic -pedantic-errors -std=c89  main.cpp -pthread -lm && ./a.out