set -x;
g++-4.8 -O0 -Wall -pedantic -Wextra -pthread -std=c++11 main.cpp && ./a.out
# clang++ -O0 -Wall -pedantic -Wextra -pthread -std=c++11 -stdlib=libc++ main.cpp -lsupc++ && ./a.out