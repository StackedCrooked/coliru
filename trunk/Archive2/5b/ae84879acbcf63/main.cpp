#include <iostream>

void foo(auto x)
{
    std::cout << x;
}

int main() 
{
    foo(42);
}