#include<stdio.h>
int* fun(){
int i=5;
return (&i);}
int main()
{
    int *p=fun();
    printf("%u %d",p,*p);
    return 0;
}