#include <iostream>

template <unsigned int N>
struct FACTORIAL {
    static const unsigned int val = N * FACTORIAL<N-1>::val;
};

template <>
struct FACTORIAL<0> {
    static const unsigned int val = 1;
};

template <>
struct FACTORIAL<1> {
    static const unsigned int val = 1;
};

int main() {
    std::cout << "5! is " << FACTORIAL<5>::val << std::endl;
}