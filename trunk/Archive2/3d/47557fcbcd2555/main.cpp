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

int main(int argc, char* argv[])
{
    std::vector<std::string> words(&argv[1], &argv[argc]);
    std::cout << words << std::endl;
}
