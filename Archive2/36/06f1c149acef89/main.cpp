#include <iostream>

// g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out

class A
{
private:
//public:
    struct B
    {
        B(int i)
        {
        }

    };
};

template<int S>
class D
{
public:
    typedef A::B E;

    E f(E e)
    {
        std::cout << "hello";
        return 2;
    }
};

int main()
{
    typedef D<1> D1;
    D1 d;
    
    D1::E e(1);
    
    auto e2 = d.f(1);
    return 0;
}
