#include <stdio.h>
#include <stdlib.h>


int main()
{
    int i,n;
    int res1,res2=0;
    printf("Enter the Number: ");
    scanf("%d",&n);
    for(i=1; i<=n; i++)
    {
        if (n==i*i)  res1=1;
        if(n==(i*(1+i))/2) res2=1;
    }

    if(res1+res2==2)
    {
        printf("it is a square number and triangular number");
        return 0;
    }
    if(res1==1) printf("it is a square number");
    if(res2==1) printf("it is a triangular number");
    return 0;
}


