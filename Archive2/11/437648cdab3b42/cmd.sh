clang++ -std=c++11 -O0 -g main.cpp -o raw && ./raw > raw.out
clang++ -std=c++11 -O0 -g main.cpp -DUNIQUE -o unique && ./unique > unique.out
pr -m -t ./raw.out ./unique.out