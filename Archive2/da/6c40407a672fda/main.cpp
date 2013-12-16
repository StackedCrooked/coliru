#include <iostream>

struct A
{
    virtual ~A() {}
    virtual void foo() const = 0;
};

struct B
{
    virtual ~B() {}

    // B::foo does not *DOES NOT* override A::foo
    void foo() const { std::cout << "B::foo\n" ; }

    virtual void bar() const = 0 ;
};

struct C : A, B
{
    // override A::foo, forward to B::foo
    virtual void foo() const override { B::foo() ; }

    virtual void bar() const override { std::cout << "C::bar\n" ; }
};

int main()
{
    C c ;
    A& a = c ;
    a.foo() ; // B::foo
}
