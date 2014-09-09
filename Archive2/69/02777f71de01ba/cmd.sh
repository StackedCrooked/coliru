set -x
clang++ -O2 -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out
g++ -O2 -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out