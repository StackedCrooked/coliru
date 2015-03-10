#include <iostream>

template <class T, class W>
struct A
{
    void foo();
};

template <class T, class W>
class A<T*, W>
{
    void foo();
};

int main(){  }