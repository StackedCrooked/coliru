template<class T>
void hello();

template<template<class> class G>
G<int> say();

int main()
{
    say<hello>();
}