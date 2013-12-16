#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<int> v = {3, 1, 5, 0, 2, 8, 4, 3, 7, 6};
    
    for (auto x : v)
        std::cout << x << std::endl;
        
        
    for (auto x : v) [&x]() {
        std::cout << x << std::endl;
    }();
}
