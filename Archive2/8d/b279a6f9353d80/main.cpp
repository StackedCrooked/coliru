#include <iostream>
#include <string>
#include <vector>

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
    std::vector<int> v;
    v.push_back(1);
    v.push_back(13);
    v.push_back(2);
    for(auto x: v)
        std::cout << x << std::endl;
    std::cout << v << std::endl;
}
