#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K,V>& dict)
{
    for (auto& el : dict)
    {
        os << el.first << ": "  << el.second << std::endl;
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::unordered_map<int, std::string> dict;

    dict.emplace(10, "test10");
    dict.emplace(11, "test11");
    dict.emplace(12, "test12");

    std::cout << dict << std::endl;
}
