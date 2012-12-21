#include <iostream>

template<template<typename> class T>
struct A : T< A<T> > // OK?
{
    A()
    {
        puts(__PRETTY_FUNCTION__);
    }
};

template<class> struct B
{
    B()
    {
        puts(__PRETTY_FUNCTION__);
    }
};


int main()
{
    A<B>();
}