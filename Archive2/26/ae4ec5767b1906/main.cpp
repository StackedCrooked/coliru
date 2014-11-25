#include <iostream>

struct A
{
    void helloMe()
    {
        std::cout << "hej da!\n";
    }
};

struct B
{
    B(A& a): 
        m_a(a)
        {
            std::cout << "B got constructed!\n"; 
        }

A& m_a;
};

struct C : A, B 
{
    C() : 
        A(),
        B(*this)
        { std::cout << "C got constructed!\n";
        }
};

int main() 
{

    C c;
    c.m_a.helloMe();

    std::cin.get();
    return 0;
}
