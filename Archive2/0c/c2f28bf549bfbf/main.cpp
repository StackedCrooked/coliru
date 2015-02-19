#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

template <int I>
struct s
{
    string str;
};

template <template<int> class T, int U>
void foo_helper(const volatile T<U>&);

template <template<int> class T, int U>
void foo_helper(const volatile T<U>&&);

template<class T> struct get_tplPara;
template<template<int> class T, int U>
struct get_tplPara<T<U>>
{
    static const int u = U;
};

template <typename T, typename = decltype(foo_helper(std::declval<T>()))>
void foo(T&& param)
{
  cout << "IsRvalue: " << std::is_reference<T>::value << " - TplPara: " << get_tplPara<typename std::remove_reference<T>::type>::u << endl;
}

int main()
{
    s<5> thing;
    foo( thing );
    foo( s<3>() );
}