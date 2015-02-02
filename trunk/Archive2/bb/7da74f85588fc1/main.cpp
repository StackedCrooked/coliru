#include<stdio.h>

int countzeros(int arr[],int n)
{
    int l=0,r=n-1,m=0;
    while(l+1<r)
    {
        m = l+r / 2;
        if(arr[m] == 0)
            l = m;
        else        
            r = m-1;
    }
    if(arr[r] == 0)
        return r+1;
    if(arr[l] == 0)
        return l+1;
    return -1;
}

int main()
{
    int arr[]={0,0,0,0,0,32,8,11,10,15,22};
    int n=0;
    n = sizeof(arr)/sizeof(int);
    printf("Number of Zeros: %d\n",countzeros(arr,n));
}