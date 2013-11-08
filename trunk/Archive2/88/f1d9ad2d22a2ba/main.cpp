#include <iostream>
#include <utility>
 
template<class T>
void func_1(const T& t)
{
    static_assert(std::is_same<T, bool>::value, "");
    static_assert(std::is_same<decltype(t), const bool&>::value, "");
}
 
template<class T>
void func_2(volatile T* t)
{
    static_assert(std::is_same<T, int>::value, "");
    static_assert(std::is_same<decltype(t), volatile int*>::value, "");
}
 
template<class T>
class Foo {};
 
class Boo : public Foo<int> {};
 
template<template <class> class T1, class T2>
void func_3(T1<T2>* t)
{
    static_assert(std::is_same<T1<T2>, Foo<int>>::value, "");
    static_assert(std::is_same<T2, int>::value, "");
    static_assert(std::is_same<decltype(t), Foo<int>*>::value, "");
}
 
int main()
{
    bool a = false;
    static_assert(std::is_same<decltype(a), bool>::value, "");
    // transformed A = 'bool'
    // deducted A can be more cv-qualified = 'const bool'
    func_1(a);
 
    int* b = nullptr;
    static_assert(std::is_same<decltype(b), int*>::value, "");
    // transformed A = 'int*'
    // converted via qualification conversion to deducted A = 'volatile int*'
    func_2(b);
 
    Boo c;
    static_assert(std::is_same<decltype(&c), Boo*>::value, "");
    // transformed A = 'Boo*'
    // can be a derived class, deducted A = 'Foo<int>*'
    func_3(&c);
 
    std::cout << "done\n";
}