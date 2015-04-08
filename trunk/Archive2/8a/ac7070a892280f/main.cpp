#include <cmath>
#include <iomanip>
#include <iostream>
#include <cfloat>

 
int main()
{
    float from1 = 1e+36, to1 = std::nextafter(from1, FLT_MAX );
    
    std::cout << "The next representable float after " << std::setprecision(20) << from1
              << " is " << to1 <<"\n";
   double from2 = 1e+36, to2 = std::nextafter(from2, FLT_MAX );
    
    std::cout << "The next representable double after " << std::setprecision(20) << from2
              << " is " << to2;
}