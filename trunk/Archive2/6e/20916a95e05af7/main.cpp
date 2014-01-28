#include <iostream>

int main()
{
    constexpr unsigned long long DIVISOR_10_DIGITS = 10000000000 ;
    unsigned long long result = 0;

    for( unsigned int n = 1 ; n < 1001 ; ++n )
    {
        unsigned long long n_pow_n = n ;
        for( unsigned int i = 1 ; i<n ; ++i )
        {
            n_pow_n *= n ;
            n_pow_n %= DIVISOR_10_DIGITS ;
        }

        result += n_pow_n ;
        result %= DIVISOR_10_DIGITS ;
    }

    std::cout << result << '\n' ;
}
