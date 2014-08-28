#include <iostream>
template<class T>
void print_type()
{ std::cout << __PRETTY_FUNCTION__ << "\n"; }


template<class T>
struct Yin
{
    T* m_ptr;
};

template<class T>
struct Yang
{
    T* m_ptr;
};


template<template<class> class TT0, template<class> class TT1>
struct type_factory
{
    struct foo : TT0<TT1<foo>> {};
    struct bar : TT1<foo> {};
};


int main()
{
    type_factory<Yin, Yang>::foo x;
    print_type<decltype(x)>();
    print_type<decltype(x.m_ptr)>();
    print_type<decltype(x.m_ptr->m_ptr)>();
    print_type<decltype(x.m_ptr->m_ptr->m_ptr)>();
    
    std::cout << "\n";
    
    type_factory<Yin, Yang>::bar y;
    print_type<decltype(y)>();
    print_type<decltype(y.m_ptr)>();
    print_type<decltype(y.m_ptr->m_ptr)>();
    print_type<decltype(y.m_ptr->m_ptr->m_ptr)>();
    
    y.m_ptr = &x;
    x.m_ptr = &y;
}