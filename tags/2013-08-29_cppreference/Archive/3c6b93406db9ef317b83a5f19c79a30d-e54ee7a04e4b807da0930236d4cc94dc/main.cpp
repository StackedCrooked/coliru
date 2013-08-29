#include <iostream>
#include <string>

class A
{
    public:
    A();
    ~A();
};

A::A()
{
    std::cout << "A" << std::endl;
}

A::~A() {}

int main()
{
     A a1;

    A a2 = A();

    A::A a3 = A::A();

    A* a4 = new A();

    return 0;
 }
