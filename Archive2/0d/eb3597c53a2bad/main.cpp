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
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    int sum = 0;
    std::vector<int> ints = {1,2,3,4};
    std::for_each(ints.begin(), ints.end(), [&sum](int v){sum += v;});
    std::cout << sum << std::endl;
}
