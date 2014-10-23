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

auto increment = [](auto& range, auto value)
{
    std::transform(range.begin(), range.end(), range.begin(), [value](auto i) { return i + value;});
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    increment(words, "!!!");
    std::cout << words << std::endl;
}
