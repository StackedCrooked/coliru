set -x; g++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out