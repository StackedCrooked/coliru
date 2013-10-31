#include <array>
#include <type_traits>
#include <iostream>
#include <type_traits>

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
constexpr T to_array_deduce(seq<Is...>)
{
    return T{{Is...}};
}

template<template<std::size_t> class T, class Array>
constexpr T< std::rank<Array>{} > to_array()
{
    return to_array_deduce< T< std::rank<Array>{} > >(get_extent<Array>{});
}

template<std::size_t N>
using my_container = std::array<int, N>;

int main()
{
    constexpr const auto arr = to_array< my_container, int[52][10][9] >();
    for( auto v : arr ) std::cout << v << " ";
}
