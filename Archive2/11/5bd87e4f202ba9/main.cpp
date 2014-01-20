#include <vector>
#include <iostream>
#include <iomanip>

std::vector<float> harmonic_progression( float a, float d, std::size_t nterms )
{
    std::vector<float> seq(nterms) ;

    // form the arithmetic progression
    for( std::size_t i = 0 ; i < nterms ; ++i ) seq[i] = a + i*d ;

    // take the reciprocals to get the harmonic progression
    for( float& v : seq ) v = 1/v ;

    return seq ; // return the sequence (by value)
}

int main()
{
   const std::vector<float> prog = harmonic_progression( 0.05, -0.0125, 9 ) ;

   std::cout << std::fixed << std::setprecision(2) ;
   for( float v : prog ) std::cout << std::showpos << v << ' ' ;
   std::cout << '\n' ;
}
