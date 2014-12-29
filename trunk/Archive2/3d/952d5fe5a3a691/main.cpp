#include <iostream>

namespace A
{
    extern "C" void foo(int a = 5){ std::cout << a << "1" << std::endl; }
}

namespace B
{
    extern "C" void foo(int a = 5);
}

using A::foo;
using B::foo;

int main()
{ 
    foo(); //Error 
    foo(2);
}