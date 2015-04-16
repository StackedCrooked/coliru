#include <limits>
#include <cstddef>
#include <iostream>
int main()
{  
   uint64_t max = std::numeric_limits<int8_t>::max();
   std::cout << "MAX: " << max << std::endl;
   uint64_t min = ~(int64_t)std::numeric_limits<int8_t>::min() + 1;
   std::cout << "MIN: "  << min << std::endl << std::endl;
   
   max = std::numeric_limits<int8_t>::max();
   std::cout << "MAX: " << max << std::endl;
   min = ~std::numeric_limits<int32_t>::max();
   std::cout << "MIN: "  << min << std::endl << std::endl;
   
   max = std::numeric_limits<int8_t>::max();
   std::cout << "MAX: " << max << std::endl;
   min = ~max;
   std::cout << "MIN: "  << min << std::endl << std::endl;
   
}