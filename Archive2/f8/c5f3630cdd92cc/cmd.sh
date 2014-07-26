set -x; g++-4.8 -std=c++0x -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++1y -O2 -Wall -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out