#include <cassert>

const int arr1[] = { 1, 2, 3, 4, 5 };
const int arr2[] = { 1, 2, 3, 4, 5 };
const char sarr1[] = "Arf!";
const char sarr2[] = "Arf!";

int main()
{
    
    const int* ptr1 = arr1;
    const int* ptr2 = arr2;
    const char* sptr1 = sarr1;
    const char* sptr2 = sarr2;
    
    assert( sptr1 == sptr2 );
    assert( ptr1 == ptr2 );
}
