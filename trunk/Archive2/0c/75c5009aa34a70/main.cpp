#include <cmath>
#include <iomanip>
#include <iostream>
#include <cfloat>
#include <cfenv>
 
int main()
{
    float from1 = 0, to1 = std::nextafter(from1, 1.f);
    std::cout << "The next representable float after " << std::setprecision(20) << from1
              << " is " << to1
              << std::hexfloat << " (" << to1 << ")\n" << std::defaultfloat;
 
    float from2 = 1, to2 = std::nextafter(from2, 2.f);
    std::cout << "The next representable float after " << from2 << " is " << to2
              << std::hexfloat << " (" << to2 << ")\n" << std::defaultfloat;
 
    double from3 = std::nextafter(0.1, 0), to3 = 0.1;
    std::cout << "The number 0.1 lies between two valid doubles:\n"
              << std::setprecision(56) << "    " << from3
              << std::hexfloat << " (" << from3 << ')' << std::defaultfloat
              << "\nand " << to3 << std::hexfloat << " (" << to3 << ")\n"
              << std::defaultfloat << std::setprecision(20);
 
    // difference between nextafter and nexttoward:
    long double dir = std::nextafter(from1, 1.0L); // first subnormal long double
    float x = nextafter(from1, dir); // first converts dir to float, giving 0
    std::cout << "With nextafter, next float after " << from1 << " is " << x << '\n';
    x = std::nexttoward(from1, dir);
    std::cout << "With nexttoward, next float after " << from1 << " is " << x << '\n';
 
    // special values
    {
        #pragma STDC FENV_ACCESS ON
        std::feclearexcept(FE_ALL_EXCEPT);
        double from4 = DBL_MAX, to4 = std::nextafter(from4, INFINITY);
        std::cout << "The next representable double after " << std::setprecision(6)
                  << from4 << std::hexfloat << " (" << from4 << ')'
                  << std::defaultfloat << " is " << to4
                  << std::hexfloat << " (" << to4 << ")\n" << std::defaultfloat;
        if(std::fetestexcept(FE_OVERFLOW)) std::cout << "   raised FE_OVERFLOW\n";
        if(std::fetestexcept(FE_INEXACT)) std::cout << "   raised FE_INEXACT\n";
    } // end FENV_ACCESS block
 
    float from5 = 0.0, to5 = std::nextafter(from5, -0.0);
    std::cout << "std::nextafter(+0.0, -0.0) gives " << std::fixed << to5 << '\n';
}