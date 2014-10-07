#include <iostream>
#include <array>
#include <limits>
#include <cstdint>
#include <cmath>

int main()
{
    std::array<float, 2> fs;
    float nan = std::numeric_limits<float>::quiet_NaN();
    fs.fill(nan);
    
    for (auto& f: fs)
    {
        if (std::isnan(f))
        {
            f = 10;
        }
        std::cout << f << std::endl;
        if (*reinterpret_cast<uint32_t*>(&f) == *reinterpret_cast<uint32_t*>(&nan))
        {
            f = 10;
        }
        std::cout << f << std::endl;
    }
    
}
