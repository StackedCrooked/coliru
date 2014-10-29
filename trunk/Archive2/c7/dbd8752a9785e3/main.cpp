#include <iostream>
#include <cstdlib>
 
int compare_ints(const void* a, const void* b)   // comparison function
{
    return (*(int *)a > *(int *)b);

}
 
int main()
{
    int a[] = { 8,5,6,6,3,6,7,5,8,2,7,4,6,5,8 };
    constexpr std::size_t size = sizeof(a)/sizeof(int);
 
    std::qsort(a, size, sizeof(int), compare_ints);
 
    for (int ai : a) std::cout << ai << ' ';
}