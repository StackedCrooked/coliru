#include <iostream>

class A
{
public:
    virtual ~A() { std::cout << "A Destructor" << std::endl; }
};

class B : public A
{
public:
    ~B() { std::cout << "B Destructor" << std::endl; }
};

class C : public B
{
    // Let the compiler implement this destructor
    // Nothing will print, but virtual calls to destructor still propagate up.
};

class D : public C
{
public:
    virtual ~D() { std::cout << "D Destructor" << std::endl; }
};

int main()
{
    A* a = new D;
    delete a;
}