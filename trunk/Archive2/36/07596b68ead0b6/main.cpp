template<typename... ARGS>
struct foo {};

#include <iostream>

template<typename T>
struct bar
{
    void print() { std::cout << "primary template\n"; }
};

template<template<typename...> class T , typename... ARGS>
struct bar<T<ARGS...>>
{
    void print() { std::cout << "T<ARGS...> partial specialization\n"; }
};

template<typename... ARGS>
struct bar<foo<ARGS...>>
{
    void print() { std::cout << "foo<ARGS...> partial specialization\n"; }
};

int main()
{
    bar< foo<int, double> >{}.print();
}