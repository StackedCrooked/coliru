#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
    constexpr auto len = 10;
    auto vec = std::vector<int>(len);
    std::iota(begin(vec), end(vec), 0);
    
    using namespace std;
    
    std::cout << count_if(vec.begin(), vec.end(), std::bind(logical_not<bool>(), std::bind(modulus<int>(), placeholders::_1, 2)));
}