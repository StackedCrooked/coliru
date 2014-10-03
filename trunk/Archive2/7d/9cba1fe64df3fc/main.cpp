class normal_class {};
template<class...> class templated_class {};

template<class T> class wrapper {};

template<class T>
wrapper<T> wrap();
template<template<class...> class TT, class... Args>
wrapper< TT<Args...> > wrap();

#define concat(A, B) A ## B
#define econcat(A, B) concat(A, B)
#define first_va(T, ...) T
#define createwrapper(...) using econcat(first_va(__VA_ARGS__, dummy), _wrapper) = decltype(wrap<__VA_ARGS__>())
    
createwrapper(normal_class);
createwrapper(templated_class,int);

#include <iostream>
template<class T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    print_type<normal_class_wrapper>();
    print_type<templated_class_wrapper>();
}