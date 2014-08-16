/* note- ptoa is pointer to an array
aofp is array of pointer */

#include<stdio.h>

int main()
{
     int i;
     int arr[3]={1,2,3};    // integer array with 3 integers
     int* ptoa = arr;       // pointer to an array
     
     int* aofp[3];          // this is array of pointer
     aofp[0] = ptoa;        // here i am storing pointer to an element of array
     aofp[1] = ptoa+1;      // here i am storing pointer to an element of array
     aofp[2] = ptoa+2;      // here i am storing pointer to an element of array

     /* here i am trying to print all element of arr[3]
        using aofp i.e array of pointer*/

     for(i=0;i<3;i++)
         printf("%d", *aofp[i]);  
}