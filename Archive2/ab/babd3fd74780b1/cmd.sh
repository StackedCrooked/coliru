set -x
clang++ -O2 -stdlib=libc++ -std=c++1y -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out