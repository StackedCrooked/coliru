#include <iostream>

template<typename... Ts>
void foo() 
{
    std::cout << "More than 1" << std::endl;
}

template<> void foo()
{
    std::cout << "0" << std::endl;
}

template<int> void foo(int x)
{
    std::cout << "1" << std::endl;
}

int main()
{
    foo();
    foo(1); // I want this to call foo(int)
}