#include <iostream>


int array[3] = { 101, 102, 103 };


int main()
{
    long pval_101 = reinterpret_cast<long>(&array[0]);
    
    std::cout << *reinterpret_cast<int*>(pval_101 + 0 * sizeof(int)) << std::endl;
    std::cout << *reinterpret_cast<int*>(pval_101 + 1 * sizeof(int)) << std::endl;
    std::cout << *reinterpret_cast<int*>(pval_101 + 2 * sizeof(int)) << std::endl;
}
