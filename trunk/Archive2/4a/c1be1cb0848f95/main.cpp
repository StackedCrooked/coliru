#include <iostream>
#include <stack>

int primt_and_sum_digits( int number )
{
    std::stack<int> digits ;
    int sum = 0 ;

    while( number != 0 )
    {
        const int least_significant_digit = number % 10 ;

        digits.push( least_significant_digit ) ; 
        sum += least_significant_digit ;

        number /= 10 ;
    }

    // print digits from top of the stack (reverse order of push) till it is empty
    while( !digits.empty() )
    {
        std::cout << digits.top() << ", " ;
        digits.pop() ;
    }

    return sum ;
}

int main()
{
    for( int v : { 12, 345, 6789, 12345678 } ) // invariant: v is positive
    {
        std::cout << "The number is " << v << ",  its digits are " ;
        const int sum = primt_and_sum_digits(v) ;
        std::cout << "  and their sum is " << sum << ".\n" ;
    }
}
