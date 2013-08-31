#include <array>
#include <vector>

/* Primary template left empty, yielding an SFINAE-friendly failure */
template<typename Specialization, typename Target>
struct rebind {};

/* Sensible default: assume first parameter is for the target */
template<template<typename...> class Cont, typename T, typename... Ts, typename Target>
struct rebind<Cont<T, Ts...>, Target> {
    using type = Cont<Target, Ts...>;
};

/* Special-case */
template<typename Old, std::size_t N, typename Target>
struct rebind<std::array<Old, N>, Target> {
    using type = std::array<Target, N>;
};

template<typename Specialization, typename Target>
using Rebind = typename rebind<Specialization, Target>::type;

template<typename Target, typename Cont>
Rebind<Cont, Target> f(Cont);

int main()
{
    f<double>(std::array<int, 12> {});
}