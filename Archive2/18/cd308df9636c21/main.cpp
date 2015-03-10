#include <iostream>
#include <cmath>
#include <iomanip>

double phi( double x, double mu, double sigma )
{ return 0.5 +  0.5 * (  std::erf( (x-mu) / ( std::sqrt(2.0) * sigma ) ) ) ; }

int main()
{
    const double mu = 10 ;
    const double sigma = 3 ;

    std::cout << "\nmu: " << mu << " sigma: " << sigma << std::fixed 
              << "\n\npercent chance of number being bwtween 9.5 and 10.5 is: " 
              << std::setprecision(8) << 100 * ( phi( 10.5, mu, sigma ) - phi( 9.5, mu, sigma ) ) << "\n\n" ;             

    for( double x = 7.5 ; x < 14.1 ; x += 0.5 )
        std::cout << std::setprecision(2) << std::setw(5) << x
                  << std::setprecision(8) << std::setw(12)  << phi( x, mu, sigma ) << '\n' ;
                  
                  
}
