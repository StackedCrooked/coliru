#include <iostream>
using namespace std;

struct HEAP
{
    int* array;
    int size;
};

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b;  
    *b = t; 
}

void Heapify(struct HEAP* Heap, int idx)
{
    int largest = idx;  // Initialize largest as root
    int left = (idx << 1) + 1;  // left = 2*idx + 1
    int right = (idx + 1) << 1; // right = 2*idx + 2
 
    if (left < Heap->size && 
        Heap->array[left] > Heap->array[largest])
        largest = left;
 
    if (right < Heap->size && 
        Heap->array[right] > Heap->array[largest])
        largest = right;
 
    // Change root, if needed
    if (largest != idx)
    {
        swap(&Heap->array[largest], &Heap->array[idx]);
        Heapify(Heap, largest);
    }
}
 
// A utility function to create a max heap of given capacity
struct HEAP* BuildHeap(int *array, int size)
{
    int i;
    struct HEAP* Heap;
    Heap->size = size;   // initialize size of heap
    Heap->array = array; // Assign address of first element of array
 
    for (i = (Heap->size)/2; i >= 0; i--)
        Heapify(Heap, i);
    
    return Heap;
}

// The main function to sort an array of given size
void heapSort(int* array, int size)
{
    struct HEAP* Heap = BuildHeap(array, size);
 
    while (Heap->size > 1)
    {
        swap(&Heap->array[0], &Heap->array[Heap->size - 1]);
        --Heap->size;  // Reduce heap size
 
        // Finally, heapify the root of tree.
        Heapify(Heap, 0);
    }
}

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
    //merge_sort(array, size, 0, size-1);
    heapSort(array, size);
    
    for(int i=0; i<size; i++)
    {
        cout << array[i] << endl;   
    }
}