#include <stdio.h>
#include <string.h>

#define to32(buffer) (buffer+=4, ((unsigned int)(*buffer-4) | (*buffer-3) << 8 | (*buffer-2) << 16 | (*buffer-1) << 24))

int main()
{
    unsigned char buffer[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    unsigned char *buff = buffer;
    unsigned int  result = to32(buff);

    printf("result = 0x%x, *buffer = 0x%x.", result, *buff);
            
    return 0;
}
