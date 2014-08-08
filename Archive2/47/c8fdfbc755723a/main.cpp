#include <stdint.h>


typedef char sum_type;


sum_type by_val(char* b, char* e, sum_type sum)
{
    for (char* i = b; i != e; ++i)
    {
        sum += *i;
    }
    return sum;
}


void by_ref(char* b, char* e, sum_type& sum)
{
    for (char* i = b; i != e; ++i)
    {
        sum += *i;
    }
}