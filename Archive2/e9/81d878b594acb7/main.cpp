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
    return os << '(' << vec.size() << ')';
}

int main()
{
    std::vector<std::string> words1(6);
    std::vector<std::string> words2;
    words2.reserve(6);
    std::cout << words1 << std::endl;
    std::cout << words2 << std::endl;
}
