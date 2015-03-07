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
    int i = 0;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!!"
    };
//    while (1)
    {
        std::cout << words << ++i << std::endl;
    }
}
