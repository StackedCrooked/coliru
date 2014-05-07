#include <iostream>
#include <type_traits>

template<typename... Ts>
struct list
{};

template<typename, typename , typename = void>
struct eval;

template<typename...> struct foo {};

template<template<typename...> class F, typename... Fs, typename... Args>
struct eval<F<Fs...>,list<Args...>,typename std::enable_if<!std::is_same<F<>,foo<>>::value>::type>
{
    enum { value = 1 };
};

template<typename... Args , typename... placeholders>
struct eval<foo<placeholders...>,list<Args...>>
{
    enum { value = 2 };
};

template<typename E , typename... ARGS>
using evl = eval<E,list<ARGS...>>;

int main()
{
    std::cout << evl<foo<int>,int>::value << std::endl;
}
