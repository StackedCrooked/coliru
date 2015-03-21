#include<iostream>

class A
{
public:
    template<class T>
    void foo(T t){ std::cout << "foo()" << std::endl; }
};

template void A::foo<int>(int t);
template void A::foo<A*>(A* t);

int main(){ A a; a.foo(5); };