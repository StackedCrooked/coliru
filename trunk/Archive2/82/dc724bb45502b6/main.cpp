#include<stdio.h>
int main()
{
    int I,j,*p,*q;
    p = &I;
    q = &j;
    *p =5;
    *q = *p +I;
    printf ("%d , %d ",I,j);
}
