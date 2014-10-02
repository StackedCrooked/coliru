#include <type_traits>
#include <cstddef>

template <typename T, typename... Ts>
struct Index;

template <typename T, typename... Ts>
struct Index<T, T, Ts...> : std::integral_constant<std::size_t, 0> {};

template <typename T, typename U, typename... Ts>
struct Index<T, U, Ts...> : std::integral_constant<std::size_t, 1 + Index<T, Ts...>::value> {};

int main()
{
    static_assert(Index<int, int, double>::value == 0, "!");
    static_assert(Index<double, int, double>::value == 1, "!");
}
