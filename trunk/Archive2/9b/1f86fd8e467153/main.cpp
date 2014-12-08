#include <iostream>

auto foo = [](auto n)
{
    if(n <= 2) return n;
    return n * foo(n - 1);
};

int main()
{
    std::cout << foo(7) << std::endl;
}