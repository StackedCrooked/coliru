#include <iostream>
#include <random>

double result = 0.0 ;

void four_calcs( double a, double b )
{
    a *= b ; // multiplication
    a -= 1.2 ; // subtraction
    a /= b ; // division
    result += a ; // addition     
} 

int main()
{ 
    constexpr int NCALCS = 1800000000 ; // 1.8 billion
    constexpr int NCALLS = NCALCS / 4 ; // 4 floating point calcs per call
    
    for( int i = 0 ; i < NCALLS ; ++i ) four_calcs( i, i+1 ) ; // two conversions
    std::cout << result << '\n' ;
}
