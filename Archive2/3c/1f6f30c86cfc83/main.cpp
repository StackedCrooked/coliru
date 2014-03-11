#include <iostream>
#include <cmath>
#include <iomanip>


int main ()
{
    double values[] = { 14,  14.5,  14.5236581, 14.5256581, -14, -14.5, -14.5236,   -14.5256 } ;

    for( double v : values )
    {
        bool negative = v < 0 ;
        if(negative) { v = -v ; std::cout << '-' ; }

        long long i = std::llround( v * 100 ) ;
        long long a = i / 100 ;
        long long b = i % 100 ;

        std::cout << a ;
        if(b) std::cout << '.' << ( b%10 ? b : b/10 )  ;
        std::cout << ' ' ;
    }
    std::cout << '\n' ;
}
