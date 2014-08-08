#include <stdint.h>


typedef uint32_t sum_t;
typedef uint8_t byte_t;


sum_t by_val(byte_t* b, byte_t* e)
{
    uint32_t sum = 0;
    for (byte_t* i = b; i != e; ++i)
    {
        sum += *i;
    }
    return sum;
}


void by_ref(byte_t* b, byte_t* e, sum_t& sum)
{
    sum_t a[2] = {};
    for (byte_t* i = b; i != e; i += 2)
    {
        a[0] += i[0];
        a[1] += i[1];
    }
    sum += a[0] + a[1];
}