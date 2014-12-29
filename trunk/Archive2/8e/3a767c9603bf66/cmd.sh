set -x; clang++ -std=c++1y -O2 -Wall -pedantic -pthread main.cpp && ./a.out
g++ -std=c++1y -O2 -Wall -pedantic -pthread main.cpp && ./a.out
g++-4.8 -std=c++1y -O2 -Wall -pedantic -pthread main.cpp && ./a.out