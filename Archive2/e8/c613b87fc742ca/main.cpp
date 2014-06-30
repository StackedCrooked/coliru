#include <iostream>
#include <cmath>

    double myround(double d)
    {
      return std::floor(d + 0.5);
    }
    
    int main()
    {
        std::cout << myround( 0.5 ) << std::endl ;
        std::cout << myround( 0.4 ) << std::endl ;
        std::cout << myround( 0.49999999999999994 ) << std::endl ;
    }