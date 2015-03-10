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
    
    // test harness: verify agreement with the three-sigma rule
    for( int i = 1 ; i < 4 ; ++i )
    {
        std::cout << "within +- " << i << " sigma: " << std::setprecision(8) << std::setw(12)  
                  << phi( mu + i*sigma, mu, sigma ) - phi( mu - i*sigma, mu, sigma ) << '\n' ;
    }             
                  
}
