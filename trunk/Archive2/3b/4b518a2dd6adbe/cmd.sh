set -x ;
clang++ -O3 -march=native -pedantic -Wall -Wextra -Wconversion -std=c++11 -pthread -stdlib=libc++ main.cpp -lsupc++ && ./a.out