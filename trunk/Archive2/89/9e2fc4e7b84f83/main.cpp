#include <stdint.h>



uint32_t get_sum(uint8_t* b, uint8_t* e)
{
    uint32_t sum = 0;
    for (uint8_t* i = b; i != e; ++i)
    {
        sum += *i;
    }
    return sum;
}


void get_sum(uint8_t* b, uint8_t* e, uint32_t& sum)
{
    for (uint8_t* i = b; i != e; ++i)
    {
        sum += *i;
    }
}