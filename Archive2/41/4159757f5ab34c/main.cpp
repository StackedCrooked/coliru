#include <iostream>
#include <string>
#include <unordered_set>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::unordered_set<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << __STDC_VERSION__ << std::endl;
}
