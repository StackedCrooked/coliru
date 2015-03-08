#include <stdio.h>

void printInBinaryHelper(unsigned char i, unsigned char count = 8)
{
    if (count == 0)
        return;
        
    printInBinaryHelper(i >> 1, count - 1);
    
    printf("%c", i & 1 ? '1' : '0');
}

void printInBinary(unsigned char i)
{
    printInBinaryHelper(i);
    printf("\n");
}

int main()
{
    int i;
    
    for (i = 0; i < 256; ++i)
        printInBinary(i);
}