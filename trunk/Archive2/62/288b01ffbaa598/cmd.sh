set -x;
g++ -std=c++11 -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out
# clang++ -std=c++1y -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out