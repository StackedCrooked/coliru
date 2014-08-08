#include <stdint.h>



uint32_t by_val(char* b, char* e, uint32_t sum)
{
    for (char* i = b; i != e; ++i)
    {
        sum += *i;
    }
    return sum;
}


void by_ref(char* b, char* e, uint32_t& sum)
{
    for (char* i = b; i != e; ++i)
    {
        sum += *i;
    }
}