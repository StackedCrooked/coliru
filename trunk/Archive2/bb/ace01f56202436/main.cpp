#include <iostream>

int main()
{
    int i = 1;
    float f = 3.14;
    
    auto i2 = (true ? i : f);
    auto f2 = (false ? i : f);
    
    std::cout << i2 << std::endl << f2;
}
