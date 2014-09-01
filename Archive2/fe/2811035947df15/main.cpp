#include<stdio.h>
void main()
{
        printf("%d",fun(5));
}

void fun(int i)
{
        if(i%2) return i;
        else return i+2;
}
