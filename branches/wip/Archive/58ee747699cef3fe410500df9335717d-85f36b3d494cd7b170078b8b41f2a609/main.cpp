#include <stdio.h>

int main()
{
    signed char a = -5;
    unsigned char b = -5;
    int c = -5;
    unsigned int d = -5;

    if (a == b)
        printf("\r\n char is SAME!!!");
    else
        printf("\r\n char is DIFF!!!");

    if (c == d)
        printf("\r\n int is SAME!!!");
    else
        printf("\r\n int is DIFF!!!");

    return 0;
}