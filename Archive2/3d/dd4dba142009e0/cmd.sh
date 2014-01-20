set -x ; 
g++-4.8 -std=c++11 -O3 -Wall -pedantic -Wextra -pthread main.cpp && ./a.out
clang++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread main.cpp && ./a.out