#include <stdio.h>
void func(int ,int);
void (*fp)();
int main()
{
    fp = func;
    fp(10,20);
}
void func(int a,int b)
{
    printf("%d %d\n",a,b);
}
