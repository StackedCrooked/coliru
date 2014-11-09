#include <iostream>

int main()
{
    const int I = 3;
    auto x = 0 <= I < 7;
    
    std::cout << x << std::endl;
    
    return 0;
}
