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
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}

class LinearScanner
{
    int _imageWidth;
    std::vector<std::array<unsigned int, 13>> ScoreTable;
    LinearScanner();
};

LinearScanner::LinearScanner()
{
    _imageWidth     = 58201;
    
    ScoreTable = std::vector<std::array<unsigned int, 13>>(_imageWidth, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
};