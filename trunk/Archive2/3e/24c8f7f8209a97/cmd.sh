clang++ -std=c++14 -DHAVE_GET_IN_LAYOUT=0 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++14 -DHAVE_GET_IN_LAYOUT=1 -O2 -Wall -pedantic -pthread main.cpp && ./a.out