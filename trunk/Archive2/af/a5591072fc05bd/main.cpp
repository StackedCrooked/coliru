#include <iostream>
#include <string>
#include <boost/enable_if.hpp>

template <typename TT>
void foo(TT a, boost::enable_if<boost::is_base_of<A, TT>>::type* dummy = 0)
{
    std::cout << " ChoseRn" << std::endl;
}

class A
{
};

class B : public A
{
};

class C
{    
};

int main()
{
    A a;
    B b;
    C c;
    foo(a);
    foo(b);
    foo(c);
}