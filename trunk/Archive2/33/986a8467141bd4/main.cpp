#include <iostream>
#include <array>
#include <limits>

int main()
{
    std::array<float, 0x10> fs;
    fs.fill(std::numeric_limits<float>::quiet_NaN());
    for (auto& f: fs)
    {
        if (fs[f] == std::numeric_limits<float>::quiet_NaN())
        {
            fs[f] = 10;
        }
        std::cout << fs[f] << std::endl;
    }
    
}
