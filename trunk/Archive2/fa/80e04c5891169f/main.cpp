#include <iostream>

struct A
{
    A(){std::cout << "Constructing A" << std::endl;}
    ~A(){std::cout << "Destructing A" << std::endl;}
};

struct B
{
    B(){std::cout << "Constructing B" << std::endl;}
    ~B(){std::cout << "Destructing B" << std::endl;}
};

struct C
{
    union
    {
        A a;
        B b;
    };
    
    C(){std::cout << "Constructing C" << std::endl;}
    ~C(){std::cout << "Destructing C" << std::endl;}
    
    void use_a()
    {
        new(&a) A();
        a.~A();
    }
};

int main()
{
    C c;
    c.use_a();
}