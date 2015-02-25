#include <iostream>

void foo(const int& y)
{
    int& z = const_cast<int>(y);
    z = 4;
}

int main()
{
    int x = 3;
    foo(x);
    std::cout << x << std::endl;
    
    return 0;
}