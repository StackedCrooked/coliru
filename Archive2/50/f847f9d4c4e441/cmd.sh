set -x; clang++ -stdlib=libc++ -std=c++1y -O2 -Wall -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out
g++ -std=c++1y -O2 -Wall -pedantic -pthread main.cpp && ./a.out