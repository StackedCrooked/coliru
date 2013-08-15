#include <stdio.h>

int arr[] = {1,2,3,4,5,6,7,8};
#define SIZE (sizeof(arr)/sizeof(int))

int main()
{
        printf("SIZE = %zu, sizeof(-1) = %zu,  sizeof(SIZE) = %zu \n", SIZE, sizeof(-1), sizeof(SIZE));
        if ((-1) < SIZE)
                printf("less");
        else
                printf("more");
}