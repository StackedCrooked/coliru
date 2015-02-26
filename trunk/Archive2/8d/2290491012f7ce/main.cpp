#include <algorithm>
#include <cmath>

int main()
{
    unsigned int i= std::max<unsigned int>(std::ceil(std::fabs( 3.14)), 1 );
    //unsignedd int i2 = std::max<unsigned int>(     ceil(     fabs( 3.14, 1 )));
    return i;
}