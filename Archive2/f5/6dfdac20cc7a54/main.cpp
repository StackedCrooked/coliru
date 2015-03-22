#include <iostream>

int main()
{
    int x = 5;
    int& y = x;
    y += 5;
    
    std::cout << x << std::endl;
}