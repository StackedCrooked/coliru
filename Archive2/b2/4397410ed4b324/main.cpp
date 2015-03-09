#include <iostream>

template <class T, class W>
struct A
{
    void foo();
};

template <class T, class W>
struct A<T, W>
{
    void foo();
};

int main(){  }