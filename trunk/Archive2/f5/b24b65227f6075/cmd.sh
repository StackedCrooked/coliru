set -x ; clang++ -std=c++11 -O0 -Wall -pedantic main.cpp && ./a.out |& c++filt -t