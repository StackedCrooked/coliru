#include <iostream>

class A
{
    public: void foo() { std::cout << "foo" << std::endl; }
};

class B : public A
{
    public: void bar() { foo(); }
};

int main()
{
    B b;
    b.bar();
    
    return 0;
}