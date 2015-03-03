#include <iostream>

template<class T>
class A
{
public:
    template<class V> void foo(V v){ std::cout << "foo" << std::endl; }
};

A<int> a;
int main(){ a.foo(3); }