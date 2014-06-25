#include <iostream>

class A
{
public:
    int i;
    float f;
};

class B
{
public:
    B(int const _i, float const _f) : i(_i), f(_f) {} 
    int i = 0;
    float f = 3.14;
};


int main()
{
    A a{ 1, 0.1 };
    std::cout << a.i << " -- " << a.f << std::endl;
    B b{ 1, 0.1 };
    std::cout << b.i << " -- " << b.f << std::endl;    
    return 0;
}
