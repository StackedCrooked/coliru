#include <iostream>
#include <iomanip>
#include <cmath>

double Fx( double x )
{
    double temp = x - 3.00055 ;
    double temp2 = std::pow( temp* temp, 0.5 ) ;
    if( std::abs(temp) > 0.00001 ) temp2 = -temp2 ;
    return temp2 ;
}

int main()
{
    std::cout << std::fixed << std::setprecision(5) ;
    double x = 3.00055 ;
    std::cout << "x: " << x << "  Fx(x): " << Fx(x) << " (root)\n\n" ;

    std::cout << "now, iterating from 3.0000 in steps of 0.0001\n" ;

    bool found = false ;
    for( double x = 3.0000 ; x < 3.0010 ; x += 0.0001 )
    {
        if( Fx(x) >= 0.0 )
        {
            std::cout << "found the root!\n" ;
            found = true ;
            break ;
        }
        std::cout << "x: " << x << "  Fx(x): " << Fx(x) << '\n' ;
    }
    if( !found ) std::cout << "alas! we missed the root.\n" ;
}
