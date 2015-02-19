set -x; g++ -std=c++1y -O0 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++1y -O0 -Wall -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out