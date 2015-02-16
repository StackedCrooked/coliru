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
    A a{};
    B b{};
    std::cout << a.x << std::endl;
    std::cout << b.y << std::endl;
}
