#include <iostream>

struct A{
    A() { std::cout << "A()" << '\n'; }
    ~A() { std::cout << "~A()" << '\n'; }
};

void f(A&& a) { std::cout << "f()" << '\n'; }

int main()
{
    f(A());
}