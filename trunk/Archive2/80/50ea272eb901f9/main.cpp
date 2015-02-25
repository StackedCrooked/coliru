#include <iostream>
template<int N>
class A
{
    static const int a = A<N-1>::a; //OK, doesn't require implicit intantiation
};

template<int N>
class B
{
    static const int a = B<1>::a; //Error, implicit instantiation of template 'B<1>' within its own definition
};


int main(){ std::cout << A<15>::a << std::endl; }