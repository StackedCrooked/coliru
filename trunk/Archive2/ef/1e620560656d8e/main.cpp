#include <iostream>

template<typename, typename...>
struct eval;

template<template<typename...> class F, typename... Fs, typename Arg, typename... Args>
struct eval<F<Fs...>,Arg,Args...>
{
    enum { value = 1 };
};

template<typename...> struct foo {};

template<typename... Args>
struct eval<foo<Args...>,Args...>
{
    enum { value = 2 };
};

int main()
{
    std::cout << eval<foo<int>,int>::value << std::endl;
}
