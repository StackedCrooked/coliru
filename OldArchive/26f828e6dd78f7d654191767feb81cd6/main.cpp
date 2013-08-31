#include<stdio.h>

void prtfun(void)
{
    static int a=2; 
    int b=1;
    a+=++b;
    printf("\n %d %d" ,a ,b);
}

int main()
{
    prtfun();
    prtfun();    
    
    static int a = 1;
    a += 1;
    int b = 0;
    printf("\n %d %d", a, b);
}