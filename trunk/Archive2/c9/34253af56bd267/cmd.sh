set -x; g++ -v -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out