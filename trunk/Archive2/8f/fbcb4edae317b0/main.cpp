
#include <stdio.h>

int main()
{

    int v1 = 0x19194;
    unsigned char *p = (unsigned char*)&v1;
    printf("\\x%02x\\x%02x\\x%02x\\x%02x", p[0], p[1], p[2], p[3]);

    return 0;
}
