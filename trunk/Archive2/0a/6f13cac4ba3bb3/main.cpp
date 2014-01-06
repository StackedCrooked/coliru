#include <iostream>
struct X
{
    X() { std::cout<<"hello"; }
};

struct Y
{
    X x;
    constexpr Y() = default;
};

int main()
{
    Y y;
}