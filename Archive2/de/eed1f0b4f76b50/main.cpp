#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
        //dsfsdfsd
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!!"
    };
    std::cout << words << std::endl;
}