#include <iostream>
#include <string>
#include <vector>
#include <iostream.h>
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
    cout << "11111111111111111" << endl;
    std::cout << words << std::endl;
}
