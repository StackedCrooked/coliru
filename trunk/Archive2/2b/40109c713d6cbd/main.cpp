#include <iostream>

struct A
{
    A() { std::cout << "A()"; }
    A(const A&) { std::cout << "A(const A&)"; }
    A(A&&) { std::cout << "A(A&&)"; }
    ~A() { std::cout << "~A()"; }
};

struct B : A
{
    B() { std::cout << "B()"; }
    B(const B&) { std::cout << "B(const B&)"; }
    B(B&&) { std::cout << "B(B&&)"; }
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