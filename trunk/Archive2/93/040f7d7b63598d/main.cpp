#include <bitset>
#include <iostream>

int main()
{
    std::cout << ( std::bitset<137>( 123456789012345678 ) << 67 ) << '\n' ;
}
