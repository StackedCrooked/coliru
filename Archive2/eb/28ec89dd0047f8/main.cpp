#include <iostream>
#include <cmath>

bool is_perfect_square( unsigned int n )
{
    const double root = std::sqrt(n) ;
    const unsigned int lbound = root - 1 ;
    const unsigned int ubound = root + 2 ;
    
    for( auto i = lbound ; i < ubound ; ++i ) if( i*i == n ) return true ;
    
    return false ;
}

int main ()
{
    for( unsigned int i = 2 ; i < 1000 ; ++i )
        if( is_perfect_square( i*i*i - 4 ) ) std::cout << i << '\n' ;
}
