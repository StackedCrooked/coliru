#include <iostream>
#include <cmath>
#include <algorithm>

int main()
{
    const double EPSILON = 1.0 / 100 ;
    double a = 0;
    double b = 0;

    while ( std::cin >> a >> b ) {

        std::cout << "first number is : " << a << "\nsecond number is : " << b << "\n\n";

        if( a == b ) // check this first
            std::cout << "The numbers are equal\n";

        else { // not equal

            if ( a > b )
            {
                std::cout << "the larger value is : " << a << '\n';
                std::cout << "the smaller value is : " << b << '\n';
            }

            else   // a < b
            {
                std::cout << "the larger value is : " << b << '\n';
                std::cout << "the smaller value is : " << a << '\n';
            }

            // http://en.cppreference.com/w/cpp/numeric/math/fabs
            const double difference = std::abs( a - b ) ; // absolute value of difference

            if( difference < EPSILON ) std::cout << "Numbers are almost equal\n" ;

        } // not equal

    }// end of while
}
