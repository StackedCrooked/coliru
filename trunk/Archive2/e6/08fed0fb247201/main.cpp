#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int findduplicate(int a[], int n)
{
    int i=0,temp;
    for(i=0;i<n;i++)
    {
        temp = abs(a[i]);
        if(a[temp] < 0)
            return temp;
        a[temp]*= -1;
    }
    return -1;
}

int main()
{
    int max,i,*arr;
    max = 10;
    arr = (int*)malloc(max*sizeof(int));
    for(i=0;i<max;i++)
        arr[i] = 1 + (int)(rand() %(max-1));
    for(i=0;i<max;i++)
        printf("%d  ",arr[i]);
    printf("\n %d\n ",findduplicate(arr,max));
}