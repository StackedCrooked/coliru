#include<stdio.h>

int missing(int a[],int n)
{
    int i=0,res=0;
    for(i=0;i<n;i++)
        res = res^a[i]^i;
    res = res ^ i;
    return res;
}

int main()
{
    int arr[]={0,1,2,4,5,6};
    printf("Missing element: %d\n",missing(arr,6));
}