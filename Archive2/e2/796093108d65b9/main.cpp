#include <stdio.h>

int main()
{
    goto lb;
    static int a=5;

lb:
    goto b;
    int b=6;

b:
    printf("%d %d",a,b);
    return 0;
}