#include <iostream>

int main()
{
    const int SIZE = 10;
    int nums[SIZE] = {1,2,3,4,5,6,7,8,9,10};
    int* ptrA = nums, *ptrB = nums + SIZE - 1;
    for (int i = 1; i < SIZE; ++i) ++ptrA;
    std::cout << std::boolalpha;
    
    std::cout << (ptrA == ptrB) << '\n';
    std::cout << (*ptrA == *ptrB) << '\n';
    std::cout << (&(*ptrA) == &(*ptrB)) << '\n';
}
