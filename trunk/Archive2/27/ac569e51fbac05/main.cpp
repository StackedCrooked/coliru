#include <iostream>
#include <string>
#include <vector>

int binSearch(int *arr, int n, int num)
{
    int ibegin=0;
    int iend=n-1;
    int middle = (ibegin + iend)/2;
    while(iend >= ibegin)
    {
        middle=(ibegin+iend)/2;
        if(arr[middle]==num)
        {
            return middle;
        }
        else if(arr[middle] > num)
        {
            iend = middle-1;
        }
        else if(arr[middle] < num)
        {
            ibegin = middle+1;
        }
    }
    return -1;
}


int main()
{
    int arr[]={1,2,3,4,4,6,7,8,9,10};
    int toFind = 11;
    int pos = binSearch(arr, 10, toFind);    

    std::cout<<"Position of ["<<toFind<<"] is ["<< pos << "]" << std::endl;
}

