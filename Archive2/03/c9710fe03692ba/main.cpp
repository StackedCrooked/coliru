#include <iostream>
#include <limits>

int main()
{
    // prints 32 32 32 on most systems
    std::cout << std::numeric_limits<unsigned>::digits << " " << __builtin_ctz(0) << " " << __builtin_clz(0);    
}
