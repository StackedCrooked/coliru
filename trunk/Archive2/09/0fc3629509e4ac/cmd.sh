set -x; clang++ -std=c++11 -O -Wall -Wextra -pedantic-errors -pthread -stdlib=libstdc++ main.cpp && time ./a.out && time ./a.out arg