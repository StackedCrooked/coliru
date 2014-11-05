#include <limits>
#include <iostream>
 
int main() 
{
    std::cout << "type\tlowest\thighest\n";
    std::cout << "int64_t\t"
              << std::numeric_limits<int64_t>::lowest() << '\t'
              << std::numeric_limits<int64_t>::max() << '\n';
    std::cout << "long\t"
              << std::numeric_limits<long>::lowest() << '\t'
              << std::numeric_limits<long>::max() << '\n';
}