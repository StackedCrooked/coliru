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
    std::vector<int> first{{1, 4, 9, 9, 20, 30}};
    std::vector<int> second{{23, 25, 28, 31, 100}};
    
    std::vector<int> merged;
    merge(first.begin(), first.end(), second.begin(), second.end(), std::back_inserter(merged));
    
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    std::cout << merged << std::endl;
}
