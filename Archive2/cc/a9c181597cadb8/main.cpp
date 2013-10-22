#include <iostream>

int main()
{
    // prints 32 32 on most systems
    std::cout << __builtin_ctz(0) << " " << __builtin_clz(0);    
}
