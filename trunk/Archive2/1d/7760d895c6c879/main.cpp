#include <iostream>

enum class X
{
    a = 1,
    b = 2
};

int main()
{
    std::cout << (X::a | X::b);
}