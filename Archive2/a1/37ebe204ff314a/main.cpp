#include <array>
#include <type_traits>
#include <iostream>

template<std::size_t...> struct seq {};

template<class T, std::size_t... Is>
struct get_extent
: seq<Is...>
{ using type = T; };

template<class T, std::size_t N, std::size_t... Is>
struct get_extent<T[N], Is...>
: get_extent<T, Is..., N>
{};

template<class T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)> to_array_deduce(seq<Is...>)
{
    return {{Is...}};
}

template<class Array>
constexpr auto to_array() -> decltype( to_array_deduce<typename get_extent<Array>::type>(get_extent<Array>{}) )
{
    return to_array_deduce<typename get_extent<Array>::type>(get_extent<Array>{});
}

int main()
{
    constexpr const auto arr = to_array< int[7][11][13] >();
    for( auto v : arr ) std::cout << v << " ";
}
