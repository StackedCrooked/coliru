set -x ;
clang++ -O3 -pedantic -Wall -Wextra -Wconversion -std=c++11 -Weffc++ -pthread -stdlib=libc++ main.cpp -lsupc++ && ./a.out