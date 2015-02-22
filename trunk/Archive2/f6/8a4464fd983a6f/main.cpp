#include <stdint.h>
#include <iostream>
 
int main() 
{
    uint64_t    v1 = 58;
    uint64_t    v2 = 56;
    
    std::cout << (int64_t)(-(v1 - v2)) << std::endl;
}