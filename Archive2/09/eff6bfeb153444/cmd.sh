set -x;
g++ -std=c++11 -O2 -Wall -Wextra -pedantic  main.cpp && ./a.out
clang++ -std=c++11 -O2 -Wall -Wextra -pedantic  main.cpp && ./a.out