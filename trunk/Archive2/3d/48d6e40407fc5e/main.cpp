#include <iostream>

int main()
{
    struct A
    {
        A() { std::cout << __FUNCTION__ << " " << this << std::endl; }
        ~A() { std::cout << __FUNCTION__ << " " << this << std::endl; }
    };
    
    A a;
    {
        A a1;
    }
    A a2;
}
