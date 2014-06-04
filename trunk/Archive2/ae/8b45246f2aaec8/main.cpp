#include <type_traits>
#include <typeinfo>
#include <iostream>

template<template<typename,typename> class P, typename... Ts>
struct min_t_impl;

template<template<typename,typename> class P, typename T>
struct min_t_impl< P, T >
{
    using type = T;
};

template<template<typename,typename> class P, typename T, typename U, typename... Ts>
struct min_t_impl< P, T, U, Ts... >
{
    using V = typename std::conditional< P<T,U>::value, T, U >::type;
    using type = typename min_t_impl< P, V, Ts... >::type;
};

template<template<typename,typename> class P, typename... Ts>
using min_t = typename min_t_impl<P,Ts...>::type;

template<typename T,typename U>
using my_pred = std::integral_constant< bool, ( sizeof(T) <= sizeof(U) ) >;

int main()
{
    std::cout << typeid(min_t<my_pred, float, int, double>).name() << std::endl;
    return 0;
}
