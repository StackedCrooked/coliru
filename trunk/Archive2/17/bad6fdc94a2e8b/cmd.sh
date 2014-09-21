set -x;
@clang++ -std=c++0x -O3 -Wall -pedantic -pthread main.cpp -stdlib=libc++ && ./a.out <<< hlelo
g++ -v -std=c++0x -O3 -Wall -pedantic -pthread main.cpp && ./a.out <<< hlelo