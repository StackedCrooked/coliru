#include<iostream>

using namespace std;

void quicksort(int input[],int left,int right)
{
    int i=left,j=right; // initailizing left and right limit

    int pivot = input[(i+j)/2];

    while (i<=j)
    {
        while (input[i]<pivot)
        {
            i++;
        }


        while (input[j]>pivot) // if right side limit is greater than pivot, >p will move to left
        {
            j--;
        }

        if (i<=j) // when left limit less than right limit swap value
        {
            swap(input[i],input[j]);

            i++;
            j--;
        } // end if
    } // end of while

    if (left<j)
        quicksort(input,left,j);

    if (i<right)
        quicksort(input,i,right);
}




int main ()
{
    int input[10]= {3,7,2,1,99,10,15,74,11,31};


    quicksort(input,0,9); //calling function in main

    cout<<"the sorted numbers are:\n"; // showing sorted array

    for(int a=0; a<10; a++)
    {
        cout<< input[a]<<endl;
    }
 
}