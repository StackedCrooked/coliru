#include <stdint.h>



uint32_t by_val(uint8_t* b, uint8_t* e, uint32_t sum)
{
    for (uint8_t* i = b; i != e; ++i)
    {
        sum += *i;
    }
    return sum;
}


void by_ref(uint8_t* b, uint8_t* e, uint32_t& sum)
{
    for (uint8_t* i = b; i != e; ++i)
    {
        sum += *i;
    }
}