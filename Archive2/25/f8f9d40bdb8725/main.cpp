#include <functional>
#include <iostream>
 
template<template<class...>class U>
struct negate_predicate
{
    template<class... Ts>
    struct result {
        static constexpr bool value = !U<Ts...>::value;
    };
};

using T = negate_predicate<std::is_same>;
constexpr bool Result = T::result<int, bool>::value;
static_assert(Result, "");
 
int main()
{
    
}