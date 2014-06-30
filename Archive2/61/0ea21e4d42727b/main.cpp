#include<stdio.h>
int main()
{
    double a;
    while(scanf("%lf",&a)==1)
{
    int floor=a;
    int ceil=floor;
    if(floor-a<0 && a>0)
    {   ceil=a+1;
    printf("%d %d",floor,ceil);}
    else if(a<0 && floor-a>0)
    {   ceil=a-1;
    printf("%d %d",ceil,floor);}
    else
        printf("%d %d\n",floor,ceil);
}   return 0;
}
