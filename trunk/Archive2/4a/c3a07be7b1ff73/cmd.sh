clang++ -std=c++1z -O2 -Wall -Wextra -pedantic-errors -Wno-unused-parameter -Wno-unused-variable -pthread main.cpp -stdlib=libstdc++ && valgrind ./a.out 15 10 5 -lc++abi