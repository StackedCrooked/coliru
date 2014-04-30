set -x;
clang++ -O3 -Wall -Wextra -Wconversion -pedantic -std=c++11 -stdlib=libc++ main.cpp -lsupc++ && ./a.out
g++-4.8 -O3 -Wall -Wextra -Wconversion -pedantic -std=c++11 main.cpp && ./a.out