#include <limits>
#include <iostream>
#include <stdio.h>

namespace detail {
constexpr long double pi = 3.141592653589793238462643383279502884;
} // detail

template<typename T>
constexpr T pi() noexcept {
    return static_cast<T>(detail::pi);
}

int main() {
    std::cout << std::numeric_limits<double>::digits10 << '\n'
              << std::numeric_limits<float>::digits10 << '\n'
              << std::numeric_limits<long double>::digits10 << '\n';
    
    float test = 3.1415926535;
    float x = test;
    printf("%a\n%a\n%d", test, x, (x == test));
    printf("\n%a", pi<float>());
    printf("\n----\n");
    
    float test2 = pi<float>();
    float y = test2;
    printf("%a\n%a\n", test2, y);
}