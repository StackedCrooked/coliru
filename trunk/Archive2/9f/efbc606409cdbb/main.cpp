#include <iostream>
#include <cstdint>

union
{
    int oi;
    bool xd;
    
} loko;

int main()
{
    loko.oi = 0;
    std::cout << loko.xd << std::endl;
    loko.oi = 1;
    std::cout << loko.xd << std::endl;
}