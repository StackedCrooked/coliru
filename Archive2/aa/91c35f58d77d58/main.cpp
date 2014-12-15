#include <iostream>

struct A
{
private:
    int a = 5;
    friend int foo(A a);
};

int foo(A a)
{
    return a.a;
}

int a = foo(A());

int main(){ std::cout << a << std::endl; }