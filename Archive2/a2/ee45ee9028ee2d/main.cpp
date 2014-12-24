#include <iostream>
#include <vector>
#include <boost/circular_buffer.hpp>

int main()
{
    std::size_t M = 5 ;

    // http://www.boost.org/doc/libs/1_57_0/doc/html/circular_buffer.html
    boost::circular_buffer< std::vector<double> > ring_buffer(M) ; // keeps the last 'M' vectors

    double v = 0.1 ;
    std::size_t n = 2 ;
    for( std::size_t i = 0 ; i < M*2 ; ++i )
    {
        std::vector<double> next( n, v ) ;
        double incr = 0 ;
        for( double& d : next ) { d += incr ; incr += 0.1 ; }
        ring_buffer.push_back( std::move(next) ) ;

        for( const auto& vec : ring_buffer )
        {
            std::cout << "[ " ;
            for( double d : vec ) std::cout << d << ' ' ;
            std::cout << "] " ;
        }
        std::cout << '\n' ;

        if( i%2 ) ++n ;
        v += 0.1 ;
    }
}
