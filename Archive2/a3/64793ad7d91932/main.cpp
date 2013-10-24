#include <iostream>
#include <array>
#include <algorithm>

template< char... Cs >
bool char_match( char c )
{
    constexpr std::array< char, sizeof...( Cs ) > a {{ Cs... }};
    return std::find_if(std::begin(a), std::end(a),[c](char x){return x==c;}) != std::end(a);
}

int main()
{
    std::cout << char_match< 'a', 'b', 'c' >( 'a' ) << std::endl;
    std::cout << char_match< 'a', 'b', 'c' >( 'b' ) << std::endl;
    std::cout << char_match< 'a', 'b', 'c' >( 'c' ) << std::endl;
    std::cout << char_match< 'a', 'b', 'c' >( 'd' ) << std::endl;
}
