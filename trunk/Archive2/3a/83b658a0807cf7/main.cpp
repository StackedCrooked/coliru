#include <iostream>
#include <cmath>
// #include <cassert>
// #include <stdexcept>

float sqrt( float x )
{
    const float result = std::sqrt(x) ;

    // assert( !std::isnan(result) ) ;
    // if( std::isnan(result) ) throw std::invalid_argument( "sqrt of negative number!" ) ;
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
