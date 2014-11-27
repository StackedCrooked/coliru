#include <string>
#include <algorithm>
#include <iostream>

int main()
{
    float n = 1.0f, a;
    
    for (auto i = 0, e = 64; i != e; ++i)
    {
        a = std::nextafter(n, (std::numeric_limits<float>::max)());
        std::cout << n << " -> " << (a - n) << std::endl;
        n *= 2.0f;
    }
    return 0;
}
