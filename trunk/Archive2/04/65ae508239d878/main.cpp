//Title of this code
#include <iostream>
#include <cmath>

int main()
{
    unsigned num = 64;
    
    unsigned sqrt = std::sqrt(num + 1) + 1;
    for (unsigned i = 2; i < sqrt; ++i)
        std::cout << i << ' ' << num/i << '\n';
}