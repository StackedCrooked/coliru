set -x ; 
clang++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -stdlib=libc++ main.cpp -lsupc++ && ./a.out