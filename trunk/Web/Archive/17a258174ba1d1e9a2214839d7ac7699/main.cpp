template<template<typename> class A, template<typename> class B>
struct CombinePolicies
{
    template<typename T>
    struct rebind : A<T>, B<T>
    {
        rebind(T * p) : A<T>(p), B<T>(p) {}
    };
};


template<template<typename> class ...Args>
struct VariadicCombinePolicies
{
    template<typename T>
    struct rebind : Args<T>...
    {
        rebind(T * p) : Args<T>(p)... {}
    };
};


template<typename> struct A;
template<typename> struct B;
template<typename> struct C;


int main()
{
    typedef CombinePolicies<A, B>::rebind<int> AB;
    typedef VariadicCombinePolicies<A, B>::rebind<int> AB2;
}