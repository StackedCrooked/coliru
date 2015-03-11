#include <iostream>

namespace detail {
    template <int n, bool isNegative>
    struct factorial_impl {
        enum { value = n * factorial_impl<n - 1, isNegative>::value };
    };

    template <int n>
    struct factorial_impl<n, true> {
        enum { value = -1 };
    };

    template <>
    struct factorial_impl<0, false> {
        enum { value = 1 };
    };
    
}

template <int n>
struct factorial {
    enum { value = detail::factorial_impl<n, n < 0>::value };
};

int main() {
    std::cout << factorial<5>::value << std::endl;
    std::cout << factorial<0>::value << std::endl;
    std::cout << factorial<-5>::value << std::endl;
}