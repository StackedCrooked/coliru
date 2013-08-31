#include <stdio.h>
void clear(int bp);
main() 
{ 
  clear(4);
}

void clear (int bp)
{
    int reg = 0xFFFFFFFF;

    printf("0x%X\n", reg);
    
    if(bp >= 32)
    {
        printf("Error\n");
        return;
    }
    
    reg &= ~(1 << bp);
    
    printf("0x%X\n", reg);
    
}
