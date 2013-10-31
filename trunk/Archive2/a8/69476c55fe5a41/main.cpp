#include <array>
#include <type_traits>
#include <iostream>

template<std::size_t...> struct seq {};

template<class T, std::size_t... Is>
struct get_extent
: seq<Is...>
{};

template<class T, std::size_t N, std::size_t... Is>
struct get_extent<T[N], Is...>
: get_extent<T, Is..., N>
{};

template<class T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)> to_array_deduce(seq<Is...>)
{
    return {{Is...}};
}

template<class T, class Array>
constexpr auto to_array() -> decltype( to_array_deduce<T>(get_extent<Array>{}) )
{
    return to_array_deduce<T>(get_extent<Array>{});
}

int main()
{
    constexpr const auto arr = to_array< int, int[1][2][3] >();
    for( auto v : arr ) std::cout << v << " ";
}
