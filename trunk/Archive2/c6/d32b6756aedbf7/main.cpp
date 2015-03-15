#include <tuple>
#include <iostream>

int main()
{
    int x, y;
    std::tie(x,y) = std::make_tuple(1,2);
    std::cout << x << "," << y;
}