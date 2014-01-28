#include <iostream>
#include <cfloat>
#include <iomanip>

int main()
{
    std::cout << std::scientific << std::setprecision(20) 
              << "actual epsilon: " << DBL_EPSILON << '\n' ;

    double min_last = 10 ;

    for( double d = 1 ; d > 0.0001 ; d -= 0.0000001 )
    {
        double v = d ;

        double last_seen ;
        while( v > DBL_EPSILON )
        {
            last_seen = v ;
            v /= 2 ;
        }

        if( last_seen < min_last ) min_last = last_seen ;
    }

    std::cout << "  minimum seen: " << min_last << '\n' ;
}
