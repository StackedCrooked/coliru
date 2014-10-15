#include <iostream>

struct A
{
    A() { foo() ; }
    virtual ~A() = default ;
    virtual void foo() const { bar() ; }
    virtual void bar() const = 0 ;
};

struct B : A { virtual void bar() const override {} } ;

B b ;

int main() {}
