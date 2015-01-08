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

template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A,B>& p)
{
    os << p.first << ":" << p.second;
    return os;
}

int main()
{
    std::vector<std::pair<int,int>> words = {{1,2}, {1,2}, {1,2}};
    std::cout << words << std::endl;
}
