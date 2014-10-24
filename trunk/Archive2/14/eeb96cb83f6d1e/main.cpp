#include <iostream>
#include <bitset>

template < typename T >
const T& evaluate_with_commentary( const char* narrative, const T& v )
{
    std::cout << narrative << '\n' ;
    return v ;
}

template < typename T >
T& evaluate_with_commentary( const char* narrative, T& v )
{
    std::cout << narrative << '\n' ;
    return v ;
}

const std::bitset<64> MASK_ONE = evaluate_with_commentary( "initialise MASK_ONE", 1 ) ;

const std::bitset<64> MASK_TWO = evaluate_with_commentary( "initialise MASK_TWO", std::bitset<64>( 1U << 2U ) ) ;

int count = evaluate_with_commentary( "initialise count", 345 ) ;

int count2 = evaluate_with_commentary( "initialise count2", count ) ;

int main()
{
}
