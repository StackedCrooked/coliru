#include<stdio.h>

int main()
{
    int a[]={10,8,2,4,9,3,1,-6,20,100,-99};
    int n = sizeof(a)/sizeof(int);
    int i=0,j=0,temp=0;
    
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(a[i]>a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }        
    }
    for(i=0;i<n;i++)
        printf("%d  ",a[i]);   
    
}