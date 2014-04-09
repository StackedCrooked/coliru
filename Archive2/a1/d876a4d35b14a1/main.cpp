#include <iostream>

int i;

void foo(int x)
{
    std::cout << x << i << '\n';
}

int main()
{
    foo(i++);
    return 0;
}