#include <type_traits>

template<template<class> class T> struct is_yinyang : public std::false_type {};


template<class other, class self, class dummy = void>
struct rebind
{
    using type = other;
};

template<template<class> class other, class dummy_o, template<class> class self, class dummy_s>
struct rebind< other<dummy_o>, self<dummy_s>, typename std::enable_if<is_yinyang<other>{} && is_yinyang<self>{}>::type >
{
    using type = other< self<void> >;
};

template<class other, class self>
using rebind_t = typename rebind<other, self>::type;


//here's Yin + Specialization
template <typename T>
struct Yin {
    rebind_t<T, Yin> *m_ptr;
};
template<> struct is_yinyang<Yin> : public std::true_type {};

//here's Yang + Specialization
template <typename T>
struct Yang {
    rebind_t<T, Yang> *m_ptr;
};
template<> struct is_yinyang<Yang> : public std::true_type {};


#include <iostream>
template<class T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }


//proof of type correctness and recursability
int main() {
    Yin<Yang<void>> a {}; 
    Yang<Yin<void>> b {};
    a.m_ptr = &b;
    b.m_ptr = &a;
    
    print_type<decltype(a)>();
    print_type<decltype(a.m_ptr)>();
    print_type<decltype(a.m_ptr->m_ptr)>();
    
    std::cout << "\n";
    
    print_type<decltype(b)>();
    print_type<decltype(b.m_ptr)>();
    print_type<decltype(b.m_ptr->m_ptr)>();
    
    //proof of recursion
    auto ptr = a.m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr;
    (void)ptr;
    return 0;
}