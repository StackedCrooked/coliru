#include <iostream>
#include <cstdlib>
 
int compare_ints(const void* a, const void* b)   // comparison function
{
    int arg1 = *reinterpret_cast<const int*>(a);
    int arg2 = *reinterpret_cast<const int*>(b);
    if(arg1 < arg2) return -1;
    if(arg1 > arg2) return 1;
    return 0;
}
 
int main()
{
    int a[] = { -2, 99, 0, -743, 2, 3, 4 };
    constexpr std::size_t size = sizeof(a)/sizeof(int);
 
    std::qsort(a, size, sizeof(int), compare_ints);
 
    for (int ai : a) std::cout << ai << ' ';
}