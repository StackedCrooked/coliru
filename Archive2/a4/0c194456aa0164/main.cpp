#include <iostream>

auto f() -> auto
{
    return 5;
}

int main()
{
    std::cout << f();
}