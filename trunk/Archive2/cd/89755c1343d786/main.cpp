//#include <iostream>

int volatile dummy;

class A {
public:
    void yell() { dummy++; }
};
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};

extern "C" int bar()
{
    auto hack = new D;
    hack->yell();
    return 1;
}

