#include <string.h>
#include <stdio.h>

__attribute__((optnone)) void*
always_memset(void *b, int c, size_t len)
{
    return memset(b, c, len);
}

int main()
{
    int i = 10;
    always_memset(&i, 0, sizeof(int));
    printf("%d", i);
    return 0;    
}
