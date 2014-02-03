#include <iostream>

struct A {};
struct B : A {};

struct base
{
    void foo(B&) {std::cout<<"base::foo\n";}
};

struct derived : base
{
    using base::foo;
    void foo(A&) {std::cout<<"derived::foo\n";}
};

int main()
{
    B b;
    derived d;
    d.foo(b);
}