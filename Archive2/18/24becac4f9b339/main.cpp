#include <iostream>

class A
{
    public: 
    
    void foo() { std::cout << "foo" << std::endl; }
};

class B : public A
{
    public: 
    
    static void foo() { std::cout << "static foo" << std::endl; }
};

int main()
{
    B b;
    b.foo();
    
    return 0;
}