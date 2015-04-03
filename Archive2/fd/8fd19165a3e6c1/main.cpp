#include <iostream>
#include <type_traits>

template <std::size_t N, bool = (N > 10)>
struct clamp;

template <std::size_t N>
struct clamp<N, false> : std::integral_constant<std::size_t, N> { };

template <std::size_t N>
struct clamp<N, true> : std::integral_constant<std::size_t, 10> { };

template <std::size_t N>
void
foo_helper() {
    std::cout << N << '\n';
}

template <std::size_t N>
void
foo() {
    foo_helper<clamp<N>::value>();
}

int
main() {
    foo<5>();
    foo<15>();
}
