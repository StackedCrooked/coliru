template<bool T>
class A {
public:
    A() : valid_(T) {}
    
    int valid_;
};

#ifdef PRODUCT1
#define A_VALUE true
#else
#define A_VALUE false
#endif

class B {
public:
static A<A_VALUE> proxy_;
};

A<A_VALUE> B::proxy_;

#include <iostream>

int main()
{
    std::cout << B::proxy_.valid_ << '\n';
}
