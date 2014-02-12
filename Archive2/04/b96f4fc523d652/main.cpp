#include <cstdint>
#include <iostream>

template <uintmax_t N> 
uintmax_t const Factorial = N * Factorial<N - 1>;
template <> 
uintmax_t const Factorial<0> = 1;

int main() {
    std::cout << Factorial<5>;
    std::cout << Factorial<52>;
}