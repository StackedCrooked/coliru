set -x; 
clang++ -stdlib=libc++ -O3 -std=c++1y -Wall -pedantic -pthread main.cpp -o a.out && ./a.out