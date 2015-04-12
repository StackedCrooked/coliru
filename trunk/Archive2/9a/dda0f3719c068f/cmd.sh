set -x; clang++ -std=c++1y -stdlib=libc++ -Wall -pedantic main.cpp -pthread && ./a.out
g++ -std=c++1y -Wall -pedantic main.cpp -pthread && ./a.out