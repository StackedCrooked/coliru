set -x;
clang++ -O0 -Wall -pedantic -Wextra -pthread -std=c++1y main.cpp && ./a.out
cat main.cpp > main.c
clang -O0 -Wall -pedantic -Wextra -pthread -std=c11 main.c && ./a.out