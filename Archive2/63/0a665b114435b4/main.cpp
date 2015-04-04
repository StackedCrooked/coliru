#include <limits>
#include <cstddef>
#include <iostream>
 
int main()
{
    uint64_t max = int64_t(-1) * std::numeric_limits<int>::min();
    std::cout << max << "\n";
}