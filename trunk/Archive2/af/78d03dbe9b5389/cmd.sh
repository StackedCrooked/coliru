set -x; clang++ -stdlib=libc++ -std=c++14 -O0 -Wall -pedantic -pthread main.cpp && ./a.out
g++ -std=c++14 -O0 -Wall -pedantic -pthread main.cpp && ./a.out