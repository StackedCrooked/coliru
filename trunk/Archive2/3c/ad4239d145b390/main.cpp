
#include<stdio.h>
#include<malloc.h>
int* mergeSort(int*,int,int);

int main()
{
    int arr[] = {10,2,5,6,7,0,3,1,8};
    int i;
    int* a = mergeSort(arr,0,8);

    for(i=0;i<9;i++)
        printf("%d ",a[i]);

    printf("\n bye");
    return 0;
}

int* mergeSort(int *arr, int left, int right)
{
    int mid = (left+right)/2;
    int len = right-left+1;
    int* result = (int*) malloc(sizeof(int)*(len)), *arr1,*arr2;
    int i=0;
    int l1,l2,r1,r2;
    l2 = mid+1;

    i = 0;
    if(len < 3)
    {
        if(len == 2)
        {
            if(arr[left] > arr[right])
            {
                result[0] = arr[right];
                result[1] = arr[left] ;
            }
            else
            {
                result[0] = arr[left];
                result[1] = arr[right];
            }

            return result;
        }
        else
        {
            result[0] = arr[left];
            return result;
        }
    }

    arr1 = mergeSort(arr,left,mid);
    arr2 = mergeSort(arr,l2,right);
    l1 = 0;
    l2 = 0;
    r1 = mid-left;
    r2 = right-l2;

    while(i<len)
    {
        if(l1 > r1)
        {
            // put rest of arr2 in result and return
            while(i<len)
            {
                result[i] = arr2[l2];
                i++;
                l2++;

            }
                free(arr1);
                free(arr2);
                return result;
        }
        else if(l2 > r2)
        {
            // put rest of arr1 in result and return
            while(i<len)
            {
                result[i] = arr1[l1];
                i++;
                l1++;

            }

                free(arr1);
                free(arr2);
                return result;
        }

        if(arr1[l1] > arr2[l2])
        {
            result[i] = arr2[l2];
            l2++;
            i++;
        }
        else
        {
            result[i] = arr1[l1];
            l1++;
            i++;
        }       
    }

    free(arr1);
    free(arr2);

    //printf("Stackoverflow"); // I have to add this to make it work
    return result;
}