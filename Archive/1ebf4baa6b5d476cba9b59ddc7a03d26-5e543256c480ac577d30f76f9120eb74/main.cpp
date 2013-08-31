#include <iostream>
#include <string>
#include <vector>

class A { // header.hpp
    public:
    void foo(int i = bar);
    private:
    constexpr static int bar = 1;
}

// source.hpp
void foo(int i) {
    //do things   
}