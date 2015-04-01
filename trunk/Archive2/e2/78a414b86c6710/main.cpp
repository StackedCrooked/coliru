#include <iostream>
using namespace std;

struct MaxHeap
{
    int size;
    int* array;
};

// A utility function to swap to integers
void swap(int* a, int* b) { int t = *a; *a = *b;  *b = t; }
 
// The main function to heapify a Max Heap. The function 
// assumes that everything under given root (element at 
// index idx) is already heapified
void maxHeapify(struct MaxHeap* maxHeap, int idx)
{
    int largest = idx;  // Initialize largest as root
    int left = (idx << 1) + 1;  // left = 2*idx + 1
    int right = (idx + 1) << 1; // right = 2*idx + 2
 
    // See if left child of root exists and is greater than
    // root
    if (left < maxHeap->size && 
        maxHeap->array[left] > maxHeap->array[largest])
        largest = left;
 
    // See if right child of root exists and is greater than
    // the largest so far
    if (right < maxHeap->size && 
        maxHeap->array[right] > maxHeap->array[largest])
        largest = right;
 
    // Change root, if needed
    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}
 
// A utility function to create a max heap of given capacity
struct MaxHeap* BuildHeap(int *array, int size)
{
    int i;
    struct MaxHeap* maxHeap = 
              (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
    maxHeap->array = array; // Assign address of first element of array
 
    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

// The main function to sort an array of given size
void heapSort(int* array, int size)
{
    // Build a heap from the input data.
    struct MaxHeap* maxHeap = BuildHeap(array, size);
 
    // Repeat following steps while heap size is greater than 1. 
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  // Reduce heap size
 
        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
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