set -x; g++ -std=c++1y -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++1y -stdlib=libc++ -O2 -Wall -pedantic -pthread main.cpp && ./a.out