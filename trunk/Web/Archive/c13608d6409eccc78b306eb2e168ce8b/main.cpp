#include <stdint.h>
#include <iostream>


struct VLAN
{
    uint16_t ethertype;
    uint16_t data;
};

int main()
{    
    VLAN w = { 0 };
    
    std::cout << w.ethertype << ", " << w.data << std::endl;
}