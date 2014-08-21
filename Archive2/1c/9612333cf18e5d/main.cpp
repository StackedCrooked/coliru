#include <algorithm>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v1{1,2,3,4}, v2{4,3,2,1}, v3(4,0);
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), 
        static_cast<int const&(&)(int const&, int const&)>(std::max));
    
    for(int i : v3) {
        std::cout << i << ' ';
    }
}
