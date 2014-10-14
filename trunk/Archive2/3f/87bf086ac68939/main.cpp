#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

int main()
{
    std::vector<int> v(10);
    
    float amplitude = 3.0f;
    float frequency = 1.2f;    
    float sampleRate = 5.0f;
    
    std::generate(v.begin(), v.end(), [&, i = 0] () mutable -> short
         {
             return amplitude * std::sin((2 * M_PI * (i++) * frequency) / sampleRate);
         });
    
    for (auto e : v)
    {
        std::cout << e << ", ";
    }
}
