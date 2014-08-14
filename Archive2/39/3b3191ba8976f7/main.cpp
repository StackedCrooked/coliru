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

int main(int argc, char* args[])
{
    std::vector<std::string> words = 
    {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    int a = 0;

    std::cout << words << std::endl;
}
