template<template<typename> class X, typename Y, typename Y1> struct C;
template<template<typename> class X, typename Z> struct C<X, X<Z>, Z> {};

template<typename T> using A = T*;

int main()
{
    C<A, A<int>, int> c;
}
