#include <type_traits>
#include <cstddef>

// all this at compile-time
template<size_t N, size_t... Ints>
struct sum : std::integral_constant<size_t, N + sum<Ints...>::value> {};

template<size_t N>
struct sum<N> : std::integral_constant<size_t, N> {};

int main() {
    static_assert(sum<1, 2, 3, 4, 5, 6, 7, 8, 11, 192, 19471, 120847134>::value == 120866844, "Compile time error!");
}