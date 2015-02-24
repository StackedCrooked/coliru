#include<stdio.h>
#include<stdlib.h>

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main()
{
    int a[]={1,2,3,4,3};
    int n = sizeof(a)/sizeof(int);
    int i=0;
    
    printf("Elements before sorting:");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);

    qsort(a, n, sizeof(int), cmpfunc);
    
    printf("\nElements after sorting:");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
        
    for(i=0;i<n;i++)
    {
        if(a[i] == a[i+1])
        {
            printf("\nRepeated Element:%d\n",a[i]);
            return 0;
        }
    }    
}