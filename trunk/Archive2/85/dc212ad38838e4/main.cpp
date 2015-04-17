#include<stdio.h>

void mysubstr(char str[] , int low, int high)
{
    while(low <= high)
    {
        printf("%c",str[low]);
        //mysubstr(str,low+1,high);
        low = low+1;
    }
}


int main()
{
    char str[] = "geeksforgeeks";
    mysubstr(str,1,3);
}