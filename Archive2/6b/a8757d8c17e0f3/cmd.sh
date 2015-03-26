set -x
clang++ -O2 -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out