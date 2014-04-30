template<typename... ARGS>
struct foo {};

template<typename T>
struct bar;

template<template<typename...> class T , typename... ARGS>
struct bar<T<ARGS...>>
{
    enum { value = 1 };
};

template<typename... ARGS>
struct bar<foo<ARGS...>>
{
    enum { value = 2 };
};

template<int> void dummy();

int main()
{
    dummy<bar<foo<int>>::value>();
}
