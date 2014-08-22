#include <iostream>
#include <assert.h>

struct A 
{
    virtual ~A() {}
    virtual void f() = 0;
};
    
struct B
{
    virtual ~B() {}
    virtual void g() = 0;
};

struct C : A, B {
    virtual void f() { std::cout << "C::f()" << std::endl; }
    virtual void g() { std::cout << "D::g()" << std::endl; }
};

int main()
{
    C c;
    A* pA = &c;
    pA->f();
    B* pB = dynamic_cast<B*>(pA);
    pB->g();
    std::cout << "&c=" << (void*)&c << std::endl;
    std::cout << "pA=" << (void*)pA << std::endl;
    std::cout << "pB=" << (void*)pB << std::endl;
    std::cout << "static_cast<C*>(pB)=" << (void*)static_cast<C*>(pB) << std::endl;
    std::cout << "reinterpret_cast<C*>(pB)=" << (void*)reinterpret_cast<C*>(pB) << std::endl;
    assert(pB);
}
