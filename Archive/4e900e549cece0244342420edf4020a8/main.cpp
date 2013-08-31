template<template<typename> class ...Args>
struct VariadicCombinePolicies
{
    template<typename T>
    struct rebind : Args<T>...
    {
        rebind(T * p) : Args<T>(p)...
        {
        }
    };
};


template<typename T> struct A { A(T* = nullptr) {} };
template<typename T> struct B { B(T* = nullptr) {} };
template<typename T> struct C { C(T* = nullptr) {} };


int main()
{
    typedef CombinePolicies<A, B>::rebind<int> AB;
    typedef VariadicCombinePolicies<A, B, C>::rebind<int> ABC;
    
    int n = 1;
    ABC abc(&n);
}