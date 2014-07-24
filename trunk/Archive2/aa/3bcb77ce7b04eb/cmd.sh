set -x;
g++ -g -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out
clang++ -g -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -stdlib=libc++ main.cpp -lsupc++ && ./a.out