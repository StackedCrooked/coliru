#include <iostream>
#include <ostream>
#include <cstdint>

template<class CharT, class Traits>
std::basic_ostream<CharT,Traits>& operator<<( std::basic_ostream<CharT,Traits>& os, CharT ch )
{
    return os << static_cast<int>(ch);
}

int main()
{
    std::uint8_t val = 123;
    std::cout << val;
}
