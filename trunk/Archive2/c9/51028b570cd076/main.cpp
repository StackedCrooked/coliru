#include <iostream>
#include <iomanip>
#include <cmath>

double read_side( const char* tag )
{
    std::cout << "Please enter the " << tag << " side: " ;
    double d ;
    if( std::cin >> d && d > 0 ) return d ;

    // handle error
    // http://www.cplusplus.com/reference/ios/ios/clear/
    std::cin.clear() ; // clear input error state

    // http://www.cplusplus.com/reference/istream/istream/ignore/
    std::cin.ignore( 1000, '\n' ) ; // throw away any non-numeric input

    std::cerr << "Please enter a positive number\n" ;

    // and try again
    return read_side(tag) ;
}

int main()
{
    // floating point computations are approximate
    // if the absolute difference between x and y is less than the tolerance,
    // we want to treat them as equal
    const double tolerance = 0.0001 ;

    // read the three sides
    double a = read_side( "first" ) ;
    double b = read_side( "second" ) ;
    double c = read_side( "third" ) ;

    // make a the largest of the three
    // http://www.cplusplus.com/reference/algorithm/swap/
    if( a < b ) std::swap(a,b) ;
    if( a < c ) std::swap(a,c) ;

    // is it a triangle?
    if( a > (b+c) ) std::cerr << "These sides do not form a triangle\n" ;

    // is it right-=angled?
    // http://www.cplusplus.com/reference/cmath/abs/
    else if( std::abs( a*a - ( b*b + c*c ) ) < tolerance )
        std::cout << "Your triangle is a right triangle!\n" ;

    else
        std::cout << "I'm sorry, your triangle is not a right triangle.\n" ;
}
