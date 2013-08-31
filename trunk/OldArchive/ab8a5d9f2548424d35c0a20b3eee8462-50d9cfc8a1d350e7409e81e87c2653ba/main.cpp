#include <iostream>
int main() 
{
    auto n = 0;
    
    while (rand())
        ++n;
    
    std::cout << n << std::endl;
}