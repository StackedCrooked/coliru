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
    std::vector<int> toto(10,1);
    for(int i = 0; i < toto.size(); ++i)
    {
        std::cout << toto.at(i)<< std::endl;
    }
}
