#title Function with small-buffer-allocation
set -x
g++-4.7 -std=c++11 -O2 -Wall -pedantic main.cpp && ./a.out
g++-4.8 -std=c++11 -O2 -Wall -pedantic main.cpp && ./a.out
g++-4.9 -std=c++11 -O2 -Wall -pedantic main.cpp && ./a.out
clang++ -std=c++11 -O2 -Wall -pedantic main.cpp && ./a.out