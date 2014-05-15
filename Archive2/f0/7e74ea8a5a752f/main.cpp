#include <iostream>

class A { public: virtual void f(){ std::cout << "A::f" << '\n'; } };
class B : public virtual A {};
class C : public virtual A { public: void f(){ std::cout << "C::f" << '\n'; } };
class D : public B, public C { };

int main()
{
    D d;
    d.f();
}    