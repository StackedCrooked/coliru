#include <iostream>

struct X
{
    int& x;
};

int main()
{
    int y;
    X x { y };
    x.x = 10;
    std::cout << y << std::endl;
}