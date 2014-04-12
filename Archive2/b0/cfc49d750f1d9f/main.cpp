#include <iostream>
#include <array>
#include <string>


namespace net
{
    // IP address is array of 4 bytes
    typedef std::array<uint8_t,4> IP;
     
    std::ostream& operator<<(std::ostream& os, IP ip)
    {
        return os << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3];
            
    }
}


int main()
{
    net::IP ip = { 1, 2, 3, 4 };
    
    using net::operator<<;
    std::cout << ip << std::endl;
}
