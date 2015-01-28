#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>
 
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) < std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
    // unless the result is subnormal
           || std::abs(x-y) < std::numeric_limits<T>::min();
}
int main()
{
    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
 
    if(d1 == d2)
            std::cout << "d1 == d2\n";
    else
            std::cout << "d1 != d2\n";
 
    if(almost_equal(d1, d2, 2))
            std::cout << "d1 almost equals d2\n";
    else
            std::cout << "d1 does not almost equal d2\n";
}