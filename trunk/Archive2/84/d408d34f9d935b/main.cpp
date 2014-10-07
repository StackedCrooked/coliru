#include <iostream>
#include <string>
#include <cstdint>


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
    std::cout << "Test " << static_cast<TYPE_MARKET>(12) << std::endl;
}
