#include<stdio.h>
const int m=3;

void printspiral(int a[][m], int n)
{
    int i=0,rowstart=0,rowend=n-1,colstart=0,colend=n-1;
    while(rowstart<=rowend && colstart<=colend)
    {
        for(i=colstart;i<=colend;i++)
            printf("%d ",a[rowstart][i]);
        rowstart++;
        for(i=rowstart;i<=rowend;i++)
            printf("%d ",a[i][colend]);
        colend--;
        for(i=colend;i>=colstart;i--)
            printf("%d ",a[rowend][i]);
        rowend--;
        for(i=rowend;i>=rowstart;i--)
            printf("%d ",a[i][colstart]);
        colstart++;
    }
}


int main()
{
    int arr[][3]={{1,2,3},{4,5,6},{7,8,9}};
    printspiral(arr,3);
}
