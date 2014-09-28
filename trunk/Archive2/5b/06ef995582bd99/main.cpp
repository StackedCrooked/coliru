#include <iostream>
#include <cmath>
// #include <cassert>
// #include <stdexcept>

float sqrt( float x )
{
    const float result = std::sqrt(x) ;

    // assert( x >= 0 ) ;
    // if( x < 0 ) throw std::domain_error( "sqrt of negative number!" ) ;
    if( std::isnan(result) ) std::cerr << "result is not a number!\n" ;

    return result ;
}

int main()
{
    const float a = sqrt(3.0f);
	std::cout << a << '\n' ;

	const float b = sqrt( -3.0f );
	std::cout << b << '\n' ;
}
