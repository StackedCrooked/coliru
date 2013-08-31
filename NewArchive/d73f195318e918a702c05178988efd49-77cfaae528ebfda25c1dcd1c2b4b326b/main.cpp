#include <stdio.h>
#include <stdlib.h>

template<typename T>
struct A;

class B1 { };

template<typename S>
class B2 { };

template<>
struct A<B1> {
    template<typename S>
    void f(S x)
    {
    }
};

template<typename S>
struct A<B2<T> > {
    void f(S x)
    {
    }
};

int main() {
A<B1> first;
first.f<int>(5);

A<B2<int> > second;
second.f(5);   
}