
#define __STDC_FORMAT_MACROS 1

#include <inttypes.h>
#include <cstdio>
#include <string>

int main()
{
    int64_t n = 42;

    printf("%"PRId64"\n", n);

    return 0;
}

