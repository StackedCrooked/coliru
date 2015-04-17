#include<stdio.h>

void mysubstr(char str[] , int low, int high)
{
    if(low <= high)
    {
        printf("%c",str[low]);
        mysubstr(str,low+1,high);
    }
}


int main()
{
    char str[] = "geeksforgeeks";
    mysubstr(str,1,3);
}