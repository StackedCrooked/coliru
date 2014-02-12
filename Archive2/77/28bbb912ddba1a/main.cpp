#include <iostream>

void foo(int const& x)
{
    std::cout << x << "\n";
}

int main()
{
    const int x = 42;
    std::cout << x << "\n";
    const_cast<int&>(x) = 44;
    std::cout << x << "\n";
    foo(x);
}