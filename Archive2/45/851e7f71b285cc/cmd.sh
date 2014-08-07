set -x; g++-4.9 -std=c++1y -O0 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out abc
clang++ -std=c++1y -O0 -Wall -pedantic -pthread main.cpp  && ./a.out abc