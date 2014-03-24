#include <iostream>

int primt_and_sum_digits( int number )
{
    if( number == 0 ) return 0 ;

    const int least_significant_digit = number % 10 ; // print this at the end
                         // after the more significant digits have been printed

    const int sum = primt_and_sum_digits( number / 10 ) + least_significant_digit ;

    std::cout << least_significant_digit << ", " ;

    return sum ;
}

int main()
{
    for( int v : { 12, 345, 6789, 12345678 } ) // invariant: v is positive
    {
        std::cout << "number is: " << v << ", the digits are: " ;
        const int sum = primt_and_sum_digits(v) ;
        std::cout << " and their sum is: " << sum << ".\n" ;
    }
}
