#include <iostream>

int x;

void foo(int i)
{
    std::cout << i << std::endl;
    std::cout << x << std::endl;
}

int main()
{
    foo(x++);
}