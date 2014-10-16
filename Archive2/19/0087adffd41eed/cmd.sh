#title vtable adjustments during construction/destruction
g++ -std=c++11 -O2 -Wall -Wno-strict-aliasing -pedantic -pthread main.cpp && ./a.out