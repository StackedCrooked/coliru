#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char buffer[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    unsigned char *buff = buffer;
    unsigned int  result;
    result = *buff++;
    result += *buff++ <<8;
    result += *buff++ << 16;
    result += *buff++ <<24;

    printf("result = 0x%x, *buffer = 0x%x.", result, *buff);
            
    return 0;
}
