#include <limits>
#include <cstddef>
#include <iostream>
 
int main()
{
    uint64_t max = -std::numeric_limits<int>::min();
    std::cout << max << "\n";
}