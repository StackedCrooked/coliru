set -x;
# clang++ -O3 -Wall -Wextra -Wconversion -pedantic -std=c++11 -stdlib=libc++ main.cpp -lsupc++ && ./a.out
cat main.cpp > main.c
clang -O3 -Wall -Wextra -Wconversion -pedantic -std=c99 main.c && ./a.out