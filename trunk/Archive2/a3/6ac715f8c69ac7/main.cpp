
#include <iostream>

struct A
{
    ~A() { std::cout << "~A()"; }
};

struct B : A
{
    ~B() { std::cout << "~B()"; }
};

int main()
{
    try {
        throw B();
    }
    catch (A&) {
    }
}