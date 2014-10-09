#include <string.h>

__attribute__((optnone)) void*
always_memset(void *b, int c, size_t len)
{
    return memset(b, c, len);
}