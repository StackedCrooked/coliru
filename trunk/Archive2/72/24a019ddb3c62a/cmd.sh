set -x; clang++ -stdlib=libc++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out && echo foo
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out && echo foo