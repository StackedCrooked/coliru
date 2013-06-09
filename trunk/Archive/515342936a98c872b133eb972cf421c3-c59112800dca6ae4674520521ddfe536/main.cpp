#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits.h>
 
int idiv_ceil ( int numerator, int denominator )
{
    return numerator / denominator + (((numerator < 0) ^ (denominator > 0)) && (numerator%denominator));
}
 
void test( int n, int d )
{
    int using_float = (int) std::ceil( (double)n / d );
    int using_fn = idiv_ceil(n, d);
    std::cout << std::setw(15) << n
              << std::setw( 5) << d
              << std::setw(15) << using_float
              << std::setw(15) << using_fn
              << std::setw( 8) << ((using_float == using_fn)? "ok" : "ERROR") << std::endl;
}
 
int main(void)
{
    test(INT_MAX, 1);
    test(-INT_MAX, 1);
    test(INT_MIN, 1);
    for( int n = -5; n < 5; n++ ) {
        for ( int d = 1; d < 5; d++ ) {
            test(n, d);
            test(n, -d);
        }
    }
}
