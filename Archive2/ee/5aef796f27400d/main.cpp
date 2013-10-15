#include <cassert>



int main()
{
    const static int arr1[] = { 1, 2, 3, 4, 5 };
    const static int arr2[] = { 1, 2, 3, 4, 5 };
    const static char sarr1[] = "Arf!";
    const static char sarr2[] = "Arf!";

    const int* ptr1 = arr1;
    const int* ptr2 = arr2;
    const char* sptr1 = sarr1;
    const char* sptr2 = sarr2;
    
    assert( sptr1 == sptr2 );
    assert( ptr1 == ptr2 );
}
