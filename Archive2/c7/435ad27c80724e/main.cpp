#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

enum TYPE_MARKET : std::uint8_t
{
    ECE,
    NAFTA,
    JPN,
    OCN,
    LATAM,
    CHINA,
    KOREA,
    ROW
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    std::cout << TYPE_MARKET::ECE << std::endl;
    
    std::cout << "Test " << static_cast<TYPE_MARKET>(12) << std::endl;
}
