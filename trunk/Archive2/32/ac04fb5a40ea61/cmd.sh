clang++ -std=c++11 -O3 -march=native -S -Wall -pedantic main.cpp -o - | egrep -v '^\s*\.' | egrep -v '^\s*#' | c++filt