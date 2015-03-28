set -x ;
clang++ -O3 -pedantic -Wall -Wextra -Wconversion -std=c++11 -Wno-unused-variable -pthread -stdlib=libc++ main.cpp -lsupc++ && ./a.out
g++-4.8 -O3 -pedantic -Wall -Wextra -Wconversion -std=c++11 -Wno-unused-variable -pthread main.cpp && ./a.out