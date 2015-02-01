#include <iostream>

struct B
{
    void foo(float a){ }  
};

struct C
{
    void foo(int a){ }
};

struct A : B, C
{
    using B::foo;
    using C::foo;
} a;

int main()
{
    a.foo(5);
    a.foo(3.14f);
}
