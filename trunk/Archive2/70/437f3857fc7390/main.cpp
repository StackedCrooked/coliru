#include <iostream>
using namespace std;



void merge(int arr[], int length, int p, int q, int r)
{
    int temp[length];
    
    for (int i = p; i <= r; ++i)
	    temp[i] = arr[i];
	    
	int i=p;
	int j=q+1;
	int k=p;
	
	while (i <= q && j<= r)
	{
	    if(temp[i] <= temp[j])
	    {
	        arr[k] = temp[i];
	        ++i;
	    }
	    else
	    {
	        arr[k] = temp[j];
	        ++j;
	    }
	    ++k;
	}
	
	while (i <= q)
	{
	    arr[k] = temp[i];
	    ++k;
	    ++i;
	}
}

void merge_sort(int arr[], int length, int p, int r)
{
    if(p >= r)
        return;
        
    int q = (p+r)/2;
    merge_sort(arr, length, p, q);
    merge_sort(arr, length, q+1, r);
    merge(arr, length, p, q, r);
}

void insertion_sort (int arr[], int length)
{
    int j, temp;
		
	for (int i = 1; i < length; i++)
	{
		j = i;
		
		while (j > 0 && arr[j] < arr[j-1])
		{
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
	    }
	}
}

int main()
{
    int j=0;
    int size = 10;
    int array[size];
    for(int i=size-1; i>=0; i--)
    {
        array[j]=i;
        j++;
    }
    
    //insertion_sort(array, size);
    merge_sort(array, size, 0, size-1);
    
    for(int i=0; i<size; i++)
    {
        cout << array[i] << endl;   
    }
}