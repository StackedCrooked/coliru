#include <iostream>
#include <cstdlib>
 
int compare_ints(const void* a, const void* b)   // comparison function
{
    int* arg1 = (int*) a;
    int* arg2 = (int*) b;
    if (*arg1 < *arg2) return -1;
    else if (*arg1 == *arg2) return 0;
    else return 1;
}
 
int main()
{
    int a[] = { -2, 99, 0, -743, 2, 3, 4 };
    int size = 7;
 
    std::qsort(a, size, sizeof(int), compare_ints);
 
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << '\n';
}