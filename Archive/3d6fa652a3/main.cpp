#include <iostream>

class A {
    public:
    int foo;
    A() { foo = 1; }
};

class B : public A {
    public:
    B() { foo = 2; }
    int foo;
};


int main()
{
    A a;
    B b;
    std::cout << a.foo << std::endl;
    std::cout << b.foo << std::endl;
    std::cout << b.A::foo << std::endl;
}
