#include <iostream>
#include <type_traits>

constexpr std::size_t
clamp(std::size_t n) {
    return n > 10 ? 10 : n;
}

template <std::size_t N>
void
foo_helper() {
    std::cout << N << '\n';
}

template <std::size_t N>
void
foo() {
    foo_helper<clamp(N)>();
}

int
main() {
    foo<5>();
    foo<15>();
}
