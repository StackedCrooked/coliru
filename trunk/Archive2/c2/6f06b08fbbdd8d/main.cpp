#include <iostream>

template <class T, class W>
struct A
{
    void foo();
};

template <class T, class W>
class A<T*, W*>
{
    void foo();
};

template<class T, class W> void A<T*, W*>::foo(){ std::cout << "foo" << std::endl; }
int main(){  }