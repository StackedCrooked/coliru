template<template<typename> class A, template<typename> class B>
struct CombinePolicies
{
    template<typename T>
    struct rebind : A<T>, B<T>
    {
        rebind(T * p) : A<T>(p), B<T>(p) {}
    };
};