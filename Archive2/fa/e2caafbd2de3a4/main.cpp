#include <iostream>
#include <cstdint>
#include <sstream>
#include <utility>

char high_nibble( unsigned int v )
{
    std::ostringstream stm ;
    stm << std::hex << std::uppercase << v ;
    return stm.str().front() ;
}

char low_nibble( unsigned int v )
{
    std::ostringstream stm ;
    stm << std::hex << std::uppercase << v ;
    return stm.str().back() ;
}

std::pair<char,char> nibbles( std::uint8_t v )
{
    std::ostringstream stm ;
    stm << std::hex << std::uppercase << int(v) ;
    return { stm.str().front(), stm.str().back() } ;
}

int main()
{
    std::cout << high_nibble(171) << ' ' << low_nibble(171) << '\n' ; // A B

    const auto nibs = nibbles(171) ;
    std::cout << nibs.first << ' ' << nibs.second << '\n' ; // A B
}
