#include <iostream>
#include <type_traits>

int main()
{
    static_assert( std::is_same< decltype( 'a' ), char >::value, "type of 'a' is char" ) ;
    static_assert( std::is_same< decltype( 'a' + 'C' ), int >::value, "type of 'a' + 'C' is int" ) ;
    static_assert( std::is_same< decltype( +'a' ), int >::value, "type of +'a' is int" ) ;
    
    std::cout << 'a' << ' ' << +'a' << '\n'
              << 'C' << ' ' << +'C' << '\n'
              << "'a' + 'C' " << 'a' + 'C' << '\n' ;
}
