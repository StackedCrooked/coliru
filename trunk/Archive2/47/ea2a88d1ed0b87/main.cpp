#include <vector>
#include <iostream>
#include <numeric>

int main()
{
    std::vector<int> vs(10 - 2);
    std::iota(vs.begin(), vs.end(), 2);
    
    for(auto const& v : vs) {
        std::cout << v << ' ';
    }
}
