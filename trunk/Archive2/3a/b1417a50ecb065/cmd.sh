set -x ;
# clang++ -O0 -pedantic -Wall -Wextra -Wconversion -std=c++1y -stdlib=libc++ -pthread main.cpp -lsupc++ && ./a.out
g++-4.8 -O0 -pedantic -Wall -Wextra -Wconversion -std=c++1y -pthread main.cpp && ./a.out