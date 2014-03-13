#include <iostream>
#include <cmath>

int main() 
{
    double a[] = { 0.23, 0.37, 0.63, 0.87, 1.12, 1.34, 1.62, 1.78 } ;
    
    // http://en.cppreference.com/w/cpp/numeric/math/round
    for( double d : a ) std::cout << std::showpoint << std::llround(d*2) / 2.0 << ' ' ; 
}
