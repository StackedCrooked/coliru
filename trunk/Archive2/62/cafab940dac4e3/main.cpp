#include <iostream>
#include <cmath>

int main()
{
    for( double d : { -1.52, -1.49, 234999.5, 234999.0 } )
        std::cout << std::lround(d) << '\n' ;
}
