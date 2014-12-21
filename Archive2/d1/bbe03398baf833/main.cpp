#include <iostream>
#include <cmath>
// #include <cfenv>

long long ipow( int base, unsigned int exp )
{
    if( exp == 0 ) return 1 ;
    else if( exp == 1 ) return base ;
    else return ipow( base, exp/2 ) * ipow( base, (exp+1)/2 ) ;
}

int main()
{
    unsigned long long sum = 0 ;
    const unsigned long long upper_limit = 211111111 ;

    {
        for( int i = 0 ; i < 9 ; ++i )
        {
            sum += std::llround( std::pow( 10, i ) ) ;

            // this is just to whet your curiosity; you may ignore this for the present
            // if( std::fetestexcept(FE_INVALID) ) { /* error: out of representable range */ }
        }
        std::cout << sum << ' ' << upper_limit - 3 << '\n' ;
    }

    {
        sum = 0 ;
        for( int i = 0 ; i < 9 ; ++i ) sum += ipow( 10, i ) ;
        std::cout << sum << ' ' << upper_limit - 3 << '\n' ;
    }
}
