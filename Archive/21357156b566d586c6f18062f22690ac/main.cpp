#include <iostream>

template<template<typename> class ...Args>
struct VariadicCombinePolicies
{
    template<typename T>
    struct rebind : Args<T>...
    {
        rebind(T & t) : Args<T>(t)...
        {
        }
    };
};


template<typename T> struct A { A(T&) {} };
template<typename T> struct B { B(T&) {} };
template<typename T> struct C { C(T&) {} };


int main()
{
    typedef VariadicCombinePolicies<A, B, C>::rebind<int> ABC;
    
    int n = 1;
    ABC abc(n);
    
    std::cout << "OK" << std::endl;
    
}