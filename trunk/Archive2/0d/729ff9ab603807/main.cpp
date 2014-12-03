#include <iostream>

int volatile dummy;

class A {
public:
    void yell() { dummy++; }
};
class B : public A {};
class C : public A {};
class D : public A, public B {};

int main()
{
    return (int)(uintptr_t)(new D);    
}

