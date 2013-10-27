#include <iostream>
#include <algorithm>

bool is_palindrome( int n ) // invariant: n is a positive six digit number
{
     return n/100000 == n%10 && // first digit == last digit
             (n/10000)%10 == (n/10)%10 && // second digit == fifth digit
             (n/1000)%10 == (n/100)%10 ; // third digit == fourth digit
}

int main()
{
    int max_so_far = 100001 ;
    int first = 0 ;
    int second = 0 ;

    // the six digit numbers are of the form a * b,
    // where a and b are three digit numbers with a <= b
    // all six digit palindromes are divisible by 11
    // therefore either a or b must be divisioble by 11
    for( int a = 999 ; a > 99 ; --a )
    {
        const int min_b = std::max( max_so_far/a, a ) - 1 ;
        int init_b = 999 ;
        int decrement = 1 ;

        if( a%11 != 0 ) // a is not divisible by 11
        {
            // b must be divisible by 11
            init_b = 990 ;
            decrement = 11 ;
        }

        for( int b = init_b ; b > min_b ; b -= decrement )
        {
            const int n = a * b ;
            if( is_palindrome(n) ) // this is the largest palindrome so far
                        // (smaller ones are eliminated by our choice of min_b)
            {
               max_so_far = n ;
               first = a ;
               second = b ;
               break ;
            }
        }
    }

    std::cout << max_so_far << " (" << first << 'x' << second << ")\n" ;
}
