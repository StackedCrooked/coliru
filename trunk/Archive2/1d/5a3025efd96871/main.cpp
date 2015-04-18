#include <iostream>

struct A{ virtual ~A(){ }; };

struct B : A{ ~B() { } };

struct C : A{ ~C(){ } };

C *c = new C;

B *b = new B;

void foo (A *a)
{
    if(dynamic_cast<B*>(a))
    {
        std::cout << "Type is B*" << std::endl;
    }
    
    if(dynamic_cast<C*>(a))
    {
        std::cout << "Type is C*" << std::endl;
    }
}
    
int main()
{
    foo(c);
    foo(b);
}