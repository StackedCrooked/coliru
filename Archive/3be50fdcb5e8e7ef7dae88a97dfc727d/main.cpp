#include<stdio.h>

int a, b, c=0;
void prtfun(void);
void main()
{
static int a=1;
prtfun();
a+=1;
prtfun();
printf("\n %d %d", a, b);
}
void prtfun(void)
{
static int a=2; 
int b=1;
a+=++b;
printf("\n %d %d" ,a ,b);
}