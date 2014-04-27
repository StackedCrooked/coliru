set -x;
clang++ -O3 -std=c++11 -stdlib=libc++ main.cpp -lsupc++ && ./a.out
g++-4.8 -O3 -std=c++11 main.cpp && ./a.out