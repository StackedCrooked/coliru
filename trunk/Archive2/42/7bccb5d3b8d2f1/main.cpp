#include <iostream>
#include <memory>

template<int N>
struct factorial {
    static const int value = N * factorial<N-1>::value;
    operator int() { return value; }
};

template<>
struct factorial<0> {
    static const int value = 1;
    operator int() { return value; }
};

int main (int argc, char ** argv) {
    std::cout << factorial<4>();
}