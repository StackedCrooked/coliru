clang++ -std=c++14 -Os -Wall -pedantic -pthread main.cpp -Wextra -Wconversion && ./a.out | !c++filt -t