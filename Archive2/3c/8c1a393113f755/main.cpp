#include <stdio.h>
#include <string.h>

#define to32(buffer) ((unsigned int)*buffer++ | *buffer++ << 8 | *buffer++ << 16 | *buffer++ << 24)

int main()
{
    unsigned char buffer[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    unsigned char *buff = buffer;
    unsigned int  result = to32(buff);

    printf("result = 0x%x, *buffer = 0x%x.", result, *buff);
            
    return 0;
}
