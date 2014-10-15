#include <algorithm>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v(10);
    
    std::generate(v.begin(), v.end(), [i = 0] () mutable { return 2*(i++); });
    
    for (auto e : v)
    {
        std::cout << e << ", ";
    }
}
