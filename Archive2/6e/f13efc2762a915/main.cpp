#include <iostream>
#include <ctime>

template <typename T>
void quickSort(T arr[], int left, int right) {
    
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
    
 
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        } 
    }
    //recursion
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

template <typename T>
void quickSort(T arr[], int size) {
    std::cout << "----------------Sorting begins----------------\n";
    
    clock_t start = clock();    
    quickSort<int> (arr, 0, size - 1);
    start = clock() - start;
    
    std::cout << "Computation took " << ((double)start / CLOCKS_PER_SEC) << " seconds\n";
    std::cout << "-----------------Sorting ends-----------------\n";
}


int main()
{
    int numbers[] = {3, 45, 12, -2, -45, 54, 90, 1, 32, 86, 89};
    quickSort<int>(numbers, 11);
    for (int n: numbers)
        std::cout << n << ' ';
    return 0;
}