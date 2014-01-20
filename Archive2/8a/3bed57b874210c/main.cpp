#include <iostream>


template <unsigned int n>
struct FACTORIAL {
    static const unsigned int val = n * FACTORIAL<n-1>::val;
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
    std::cout << FACTORIAL<5>::val << std::endl;
}