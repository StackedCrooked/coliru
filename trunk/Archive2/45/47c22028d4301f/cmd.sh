set -x ; clang++ -std=c++11  -fsanitize=undefined -Wall -Wextra -Wconversion  -pedantic  -O3  -Wall -pthread main.cpp && ./a.out