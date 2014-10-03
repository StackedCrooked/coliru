#include <iostream>
#include <typeinfo>

struct A
{
    int foo() &;
};

int (A::* foo)() &; //works fine; was missing parenthesis.

struct B
{
    int (*bar)() &; //gcc accepts, but it is something else than you may think
};

int main()
{
    B b;
    std::cout << "A::foo type is " << typeid(&A::foo).name() << std::endl;
    std::cout << "foo type is " << typeid(foo).name() << std::endl;
    std::cout << "B::bar type is " << typeid(b.bar).name() << std::endl;
    return 0;
}