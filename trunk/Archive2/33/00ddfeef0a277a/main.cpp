#include <iostream>

template <class T, class W>
class A
{
    void foo(){ std::cout << "foo()" << std::endl; };
};

template <class T, class W>
struct A<T*, W>
{
    void foo(){ std::cout << "foo()" << std::endl; };
};

A<int, int> t;

int main(){ t.foo(); }