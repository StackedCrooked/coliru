clang++ main.cpp -std=c++14 -Wall -Wextra -Werror -pedantic -O2 -S -emit-llvm && cat main.ll