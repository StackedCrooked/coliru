#include <iostream>
#include <string>
#include <vector>

class A
{
    public:
        ~A()
        {
            std::cout << "Destroy A ";
            Test();
        }
        virtual void Test() { std::cout << "Test A" << std::endl; }
};

class B
{
    public:
        ~B()
        {
            std::cout << "Destroy B ";
            Test();
        }
        virtual void Test() { std::cout << "Test B" << std::endl; }
};

class C: public B, public A
{
    public:
        ~C()
        {
            std::cout << "Destroy C ";
            Test();
        }
        virtual void Test() { std::cout << "Test C" << std::endl; }
};

int main()
{
    C c;
    
    return 0;
}
