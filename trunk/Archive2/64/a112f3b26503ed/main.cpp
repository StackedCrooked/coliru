#include <iostream>

namespace A
{
    extern "C" void foo(int a = 5){ std::cout << a << "1" << std::endl; }
}

namespace B
{
    extern "C" void foo(int a = 5){ std::cout << a << std::endl; }
}

//using A::foo;
//using B::foo;

int main()
{ 
    //foo(2); //Error 
}