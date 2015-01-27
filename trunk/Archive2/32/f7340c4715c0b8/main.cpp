#include <iostream>

namespace A
{
    int b = 42;
}

namespace A
{
    int a = 24;
}

int a = A::a;

int main(){ std::cout << a << std::endl; }