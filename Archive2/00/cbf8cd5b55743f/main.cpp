#include <iostream>
struct A
{
    A(){ }
    mutable int a;
    void foo()
    {
        (*this).a = 4;
    }
};
const A a;

int main()
{
    a.a = 4;
    a.foo();
    std::cout << a.a;
}