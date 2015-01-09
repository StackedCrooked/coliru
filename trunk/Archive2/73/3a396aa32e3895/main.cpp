#include <iostream>
#include <string>
#include <vector>
#include <map>

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
    std::map<int,std::vector<char>> m;
    std::vector<char> c {'C','C','C'};
    m.insert(std::pair<int,std::vector<char>>(1,c));
    std::cout << m.at(1).size() << std::endl;
}
