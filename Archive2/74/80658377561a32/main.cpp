#include <iostream>

int a = 5;
auto f() -> decltype(auto)
{
    return a;
}

int main()
{
    std::cout << f();
    std::cout << []() -> decltype(auto) { return a; }();
}