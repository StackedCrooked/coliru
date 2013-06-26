#include <stdio.h>

int main()
{
    signed char a = -5;
    unsigned char b = -5;
    signed short c = -5;
    unsigned short d = -5;
    int e = -5;
    unsigned int f = -5;

    if (a == b)
        printf("\r\n char is SAME!!!");
    else
        printf("\r\n char is DIFF!!!");

    if (c == d)
        printf("\r\n short is SAME!!!");
    else
        printf("\r\n short is DIFF!!!");

    if (e == f)
        printf("\r\n int is SAME!!!");
    else
        printf("\r\n int is DIFF!!!");

    if (long(e) == long(f))
        printf("\r\n int is SAME!!!");
    else
        printf("\r\n int is DIFF!!!");

    return 0;
}