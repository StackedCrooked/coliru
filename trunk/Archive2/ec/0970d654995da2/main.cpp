#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a[]={1,2,3,4,3};
    int i=0,sum=0,n=sizeof(a)/sizeof(int);
    
    for(i=0;i<n;i++)
        sum +=a[i];
    
    for(i=1;i<n;i++)
        sum -= i;
        
    printf("%d\n",sum);
        
}