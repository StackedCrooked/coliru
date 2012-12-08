#include <stdint.h>


struct VLAN
{
    uint16_t ethertype;
    uint16_t data;
};


int main()
{
    VLAN v = VLAN();
    v.ethertype = 0;
}