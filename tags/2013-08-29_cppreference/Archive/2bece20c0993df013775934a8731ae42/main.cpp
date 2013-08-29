#include <iostream>
#include <limits>
#include <stdint.h>

int main()
{
    int min_int = std::numeric_limits<int>::lowest();
    min_int--;
    std::cout << min_int << std::endl;
    min_int++;
    std::cout << min_int << std::endl;
}