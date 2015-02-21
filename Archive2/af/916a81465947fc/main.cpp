#include <iostream>

template<class T>
struct A
{
    void foo();
};

template<class T> void A<T>::foo(){ std::cout << "foo" << std::endl; }

A<int>* a;
int main(){ a -> foo(); }