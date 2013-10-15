template<class>
struct A {};

template<class, class = void>
struct B {};

template<template<class, class=void> class>
struct C {};

int main()
{
    C<A> c;
}