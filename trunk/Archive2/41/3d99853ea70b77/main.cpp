#include <limits>
#include <iostream>
 
int main() 
{
    std::cout << "int64_t\t"
              << std::numeric_limits<int64_t>::lowest() << '\t'
              << std::numeric_limits<int64_t>::max() << '\n';
}