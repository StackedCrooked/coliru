#include<stdio.h>

void printsignedrange(size_t bytes)
{
    int bits = bytes*8;
    
    int from = -(1<<(bits-1));
    int to  = (1<<(bits-1)) - 1;
    
    printf("range is from %d to %d \n " , from , to);
}

void printunsignedrange(size_t bytes)
{
    int bits = bytes*8;
    
    int to = (1 << bits) -1;
    
    printf("range is from %d to %d \n ",0,to);
}


int main()
{
    printf("Signed Char: ");
    printsignedrange(sizeof(char));
    printf("UnSigned Char: ");
    printunsignedrange(sizeof(char));
}