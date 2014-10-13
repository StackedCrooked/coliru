#include <iostream>

template <class T, size_t N>
T* asFlatArray (T (&arr)[][N])
{
 (void)arr;   
}

int main() {
    
    const size_t rows = 2, columns = 5;
    int arr[rows][columns] = {
      {1, 2, 3, 4, 5},
      {6, 7, 8, 9, 0}
    };
    
    int *ptr = asFlatArray(arr);
    for (int i = 0; i < rows * columns; i++) {
        std::cout << ptr[i] << " ";
    }
}

