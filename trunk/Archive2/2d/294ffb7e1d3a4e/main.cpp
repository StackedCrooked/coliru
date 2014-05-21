#include <iostream>

namespace A
{
    void f(double) { std::cout << "f(double)" << std::endl; }
}

namespace B
{
    using A::f;
    void g();
}

namespace A
{
    void f(int) { std::cout << "f(int)" << std::endl; }
}

void B::g()
{
    f(1);
}

int main()
{
    B::g();
}