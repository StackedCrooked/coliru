set -x ;
clang++ -O3 -pedantic -Wall -Wextra -Wconversion -std=c++11 -stdlib=libc++ -pthread main.cpp -lsupc++ && ./a.out