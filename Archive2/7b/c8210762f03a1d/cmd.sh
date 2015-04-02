#title anachronistic old-style base class initializer
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | c++filt