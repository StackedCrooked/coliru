#include <cassert>

const int arr1[] = { 1, 2, 3, 4, 5 };

int main()
{
    const int arr2[] = { 1, 2, 3, 4, 5 };
    const int* ptr1 = arr1;
    const int* ptr2 = arr2;
    
    assert( ptr1 == ptr2 );
}
