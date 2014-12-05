#include <array>
#include <cstdint>
#include <iostream>


namespace networking
{
    struct IP
    {
        friend std::ostream& operator<<(std::ostream& os, IP ip)
        {
            return os << static_cast<int>(ip.bytes_[0]) << '.'
                      << static_cast<int>(ip.bytes_[1]) << '.'
                      << static_cast<int>(ip.bytes_[2]) << '.'   
                      << static_cast<int>(ip.bytes_[3]);
        }
        
        std::array<std::uint8_t, 4> bytes_;
    };
}


int main()
{
    networking::IP ip = { 1, 2, 3, 4 };
    std::cout << ip << std::endl;
}
