#include <iostream>
#include <algorithm>
#include <cmath>

void abssort(float *x, unsigned N) {
    std::sort(x, x + N,
            [](float a, float b) {
        return std::abs(a) < std::abs(b);
    });
}

int main()
{
    
    std::cout << []() { return 21;}() << std::endl ;
}

