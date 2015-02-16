#include <iostream>

struct A
{
    int x;
    A() {}
};

struct B
{
    int y;
    B() = default;
};

int main()
{
    //constexpr A a{};
    constexpr B b{};
    //std::cout << a.x << std::endl;
    std::cout << b.y << std::endl;
}
