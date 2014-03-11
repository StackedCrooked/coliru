#include <iostream>
#include <iomanip>
#include <limits>

template < typename FLOATING_POINT_TYPE > void g_function()
{
    std::cout << std::fixed << std::setprecision( std::numeric_limits<FLOATING_POINT_TYPE>::digits10 ) ;
    FLOATING_POINT_TYPE gsum = 0 ;
    for( int i = 1; i <= 99999999; ++i )  gsum += 1.0 / (100000000 - i);
    std::cout << "uncompensated summation: " << gsum << '\n' ;
    
    // http://en.wikipedia.org/wiki/Kahan_summation_algorithm
    gsum  = 0 ;
    FLOATING_POINT_TYPE compensation = 0 ;
    for( int i = 1; i <= 99999999; ++i )
    {
        FLOATING_POINT_TYPE term = 1.0 / (100000000 - i) - compensation ;
        FLOATING_POINT_TYPE temp = gsum + term ;
        compensation = ( temp - gsum ) - term ;
        gsum = temp ;
    }
    std::cout << "  compensated summation: " << gsum << "\n\n" ;
}

int main()
{
    g_function<float>() ;
    g_function<double>() ;
    g_function<long double>() ;
}
