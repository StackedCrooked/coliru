#include <iostream>
#include <string>
#include <vector>

class A
{
    public:
        void foo();
};

void A::foo()
{
    std::cout << "a.foo()" << std::endl;
}

A *a = 0;


class B
{
    public:
        ~B();
};

B::~B()
{ 
    a = new A();
};



int main()
{
    B *b = new B();
    delete b;
    a->foo();
}
