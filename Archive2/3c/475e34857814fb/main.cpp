#include <array>
#include <cstdint>
#include <iostream>


namespace networking
{
    template <typename T> struct make_it_mine { typedef T type; };
    using IP = std::array<std::uint8_t, 4>;
    
    std::ostream& operator<<(std::ostream& os, make_it_mine<IP>::type ip)
    {
        return os << static_cast<int>(ip[0]) << "."
                  << static_cast<int>(ip[1]) << "."
                  << static_cast<int>(ip[2]) << "."
                  << static_cast<int>(ip[3]);
    }
}


int main()
{
    using networking::IP;
    
    IP ip = { 1, 2, 3, 4 };
    
    std::cout << ip << std::endl;
}
