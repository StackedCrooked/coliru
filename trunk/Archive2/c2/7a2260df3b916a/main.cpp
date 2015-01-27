#include <iostream>

namespace A
{
    int b = 42;
}

int a = A::a;

namespace A
{
    int a = 24;
}

int main(){ std::cout << a << std::endl; }