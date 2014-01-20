#include <iostream>
#include <cmath> // for std::lround()
#include <iomanip>

int main()
{
    const float a[] = { -1.5f, -1.25f, -0.6f, -0.1f, 0.0f, 0.49f, 0.50f, 1.25f, 1.5f } ;

    std::cout << std::fixed << std::setprecision(2) << std::showpos  ;

    for( float f : a )
    {
        // http://en.cppreference.com/w/cpp/numeric/math/round
        const long v = std::lround(f) ;

        std::cout << f << " => " << v << '\n' ;
    }
}
