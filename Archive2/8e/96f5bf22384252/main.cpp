#include <stdio.h>

char zeroOrOne(int i)
{
    return i ? '1' : '0';
}

void printInBinaryHelper(unsigned char i, unsigned char count = 8)
{
    if (count == 0)
        return;
        
    printInBinaryHelper(i >> 1, count - 1);
    
    printf("%c", i & 1 ? '1' : '0');
}

void printInBinary(unsigned char i) { printInBinaryHelper(i); }

int main()
{
    printInBinary(10);
}