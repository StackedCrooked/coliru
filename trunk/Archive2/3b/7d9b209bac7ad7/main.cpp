#include <iostream>
#include <string>

using namespace std;

void quicksort(int arr[], int low, int high)
{
    if(low < high)
    {
        int temp = 0;
        
        int left = low;
        int right = high;
        
        
        int pivot = low;
        
        while(left < right)
        {
            while(arr[right] > arr[pivot]) right--;
            while(arr[left] <= arr[pivot]) left++;
            
            if(left < right)
            {
                temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            }//if
        }//while
        
        temp = arr[pivot];
        arr[pivot] = arr[right];
        arr[right] = temp;
        
        
        quicksort(arr, low, right - 1);
        quicksort(arr, right + 1, high);
    }
}

int main()
{
    int arr[] = {10, 23, 456, 2, 7,9,1, 102, 100, 72, 7, 5, 3, 11, 10, 90};
    
    int size = sizeof(arr) / sizeof(int);
    
    int i = 0;
    
    cout << "Before sorting" << endl;
    
    for(i = 0; i < size; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;

    quicksort(arr, 0, size - 1);

    cout << "After sorting" << endl;
    
    for(i = 0; i < size; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
    
    
    return 0;
}
