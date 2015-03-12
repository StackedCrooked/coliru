#include<stdio.h>
int (*five(int a[][3], int n))[3]
{
    for(int t=0; t<n; t++)
        a[t][t] += 5;
    return a;
}
int main()
{
    int n=3;
    int a[][3]={{1,2,3},{4,5,6},{7,8,9}};
    int (*q)[3] = five(a,n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf(" %d",q[i][j]);
        printf("\n");
    }
}
