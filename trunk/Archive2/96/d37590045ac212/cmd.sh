set -x; # g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out