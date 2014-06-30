#include <iostream>
#include <cmath>
#include <limits>

   
    float myround(float f)
    {
      return static_cast<float>( static_cast<unsigned int>( f ) ) ;
    }
    
    int main()
    {
       std::cout <<  std::numeric_limits<unsigned int>::max() << std::endl;
       std::cout << myround( 4294967296.5f ) << std::endl ;
    }