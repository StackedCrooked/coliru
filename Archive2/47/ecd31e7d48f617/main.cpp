#include <type_traits>

template<template<class,class> class T> struct is_yinyang : public std::false_type {};

//here's Yin + Specialization
template <typename T, class allowed=void>
struct Yin {
    T *m_ptr;
};
template<> struct is_yinyang<Yin> : public std::true_type {};

template <template<class,class> class other>
struct Yin<other<void,void>,typename std::enable_if<is_yinyang<other>::value>::type>
{
    other<Yin<void,void>,void> *m_ptr;
};


//here's Yang + Specialization
template <typename T, class allowed=void>
struct Yang {
    T *m_ptr;
}; 
template<> struct is_yinyang<Yang> : public std::true_type {};

template <template<class,class> class other>
struct Yang<other<void,void>,typename std::enable_if<is_yinyang<other>::value>::type>
{
    other<Yang<void,void>,void> *m_ptr;
};

//proof of type correctness and recursability
int main() {
    Yin<Yang<void>> a {}; 
    Yang<Yin<void>> b {};
    a.m_ptr = &b;
    b.m_ptr = &a;
    //proof of recursion
    auto ptr = a.m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr;
    (void)ptr;
    return 0;
}