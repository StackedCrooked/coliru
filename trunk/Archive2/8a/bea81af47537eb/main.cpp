template<class T>
void hello(T);

template<template<class> class G>
G<int> say();

int main()
{
    say<decltype(hello)>();
}