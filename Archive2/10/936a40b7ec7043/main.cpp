template<template<class>class>
struct ExpectTemplete {};

template<class T>
struct Outer
{
    template<class U>
    struct Inner {};
};

template<class T>
struct Demo : ExpectTemplete<Outer<T>::template Inner>
{
};

int main() {
    Demo<int> demo;
    (void)demo;
    return 0;
}