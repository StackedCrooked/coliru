#include <iostream>

int main()
{
    bool x = true;
    std::cout << "x=" << x << std::endl;

    int y = 2;
    x |= y;
    std::cout << "x=" << x << std::endl;
    
    x &= y;
    std::cout << "x=" << x << std::endl;
}
