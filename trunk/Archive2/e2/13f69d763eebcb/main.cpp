#include <stdio.h>

int main()
{
    int a = 2;
    int *p = &a;
    int **p2 = p;

    printf("val: %p", p2);
}
