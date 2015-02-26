#include <functional>
#include <iostream>

int main()
{
    const int a = 2;

    std::function<void(int)> f = [&](auto b) { std::cout << a << ", " << b << std::endl; };

    f(3);
}