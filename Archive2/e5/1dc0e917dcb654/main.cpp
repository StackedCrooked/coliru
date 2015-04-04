#include <limits>
#include <cstddef>
#include <iostream>
int main()
{
   uint64_t max1 = int64_t(-1) * std::numeric_limits<int>::min();
   uint64_t max2 = -std::numeric_limits<int>::min();
   std::cout << max1 << " " << max2 << "\n";
}