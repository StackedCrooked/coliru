#include <iostream>
#include <cmath>

int main()
{
    float values[] = { 123.45678901213, 123.45172901213, 123, 123.4, -123.45, 0 } ;
    std::cout << std::fixed ;
    std::cout.precision(8) ;

    for( float v : values )
    {
        float ival ;
        float fval = std::modf( v, &ival ) ;

        long before_decimalpt = std::lround(ival) ;

        // rounded to two digits after decimal point
        int after_decimalpt2 = std::lround( fval * 100 ) ;

        // rounded to four digits after decimal point
        int after_decimalpt4 = std::lround( fval * 10000 ) ;

        std::cout << v << ' ' << before_decimalpt << ' '
                   << after_decimalpt2 << ' ' << after_decimalpt4 << '\n' ;
    }
}