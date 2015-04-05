#include <iostream>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <cassert>

// algorithm from 'Hacker's Delight' by Henry S. Warren
// http://www.amazon.com/dp/0201914654 
unsigned int plus( unsigned int a,  unsigned int b )
{
    auto carry = a & b;
    auto sum = a ^ b;

    while( carry != 0 )
    {
        const auto carry_shl = carry << 1 ;
        carry = sum & carry_shl ;
        sum ^= carry_shl ;
    }

    return sum ;
}

// Note: This assumes that the signed integer value representation is two's complement
// Two's complement is almost universally used, though he C++ standard allows any
// appropriate signed integer representation.
// For instance, one's complement and sign-and-magnitude representations would be conforming
int signed_plus( int a,  int b )
{
    const long long aa = a ;
    long long result = aa + b ;
    if( result < std::numeric_limits<int>::min() || result > std::numeric_limits<int>::max() )
                    throw std::out_of_range( "signed integer overflow!" ) ;

    return int( plus(a,b) ) ;
}

int main()
{
    const int test[][2] { {12345678,0}, {-12345678,0}, {12345678,67890}, {12345678,-67890}, {-12345678,67890}, {-12345678,-67890} } ;
    for( const auto& arr : test  )
    {
         int x = arr[0] ;
         int y = arr[1] ;

         std::cout << x << " + " << y << " == " << x+y << " == " << signed_plus(x,y) << '\n' ;

         std::swap(x,y) ;
         std::cout << x << " + " << y << " == " << x+y << " == " << signed_plus(x,y) << '\n' ;

         assert( ( (x+y) == signed_plus(x,y) ) && ( (x+y) == signed_plus(y,x) ) );
    }

    try { std::cout << signed_plus( 1999999999, 2000000000 ) << '\n' ; }
    catch( const std::exception& e ) { std::cerr << "**** error: " << e.what() << '\n' ; }
}
