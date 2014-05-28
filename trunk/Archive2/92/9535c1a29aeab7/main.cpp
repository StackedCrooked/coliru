#include <iostream>
#include <typeinfo>
#include <type_traits>

template<class L, class R> 
struct smaller_size 
    : std::conditional<sizeof(L)<sizeof(R), std::true_type, std::false_type>::type
{};


//  Unspecialized version
template<template<class,class> class ordering, typename...Ts> struct Tmin;

template<template<class,class> class ordering, typename T> struct Tmin<ordering, T> 
{using type = T;};

template<template<class,class> class ordering, typename T1, typename...Ts>
struct Tmin<ordering, T1, Ts...>
{
private: using other = typename Tmin<ordering, Ts...>::type;
public:  using type = typename std::conditional<ordering<T1,other>::value, T1, other>::type;
};

int main()
{
    std::cout << typeid(Tmin<smaller_size, float, int, double>::type).name() << std::endl;
    return 0;
}