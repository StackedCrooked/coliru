#include <iostream>

constexpr int N = 10000 ;

long long pow( int a, int b ) // non-negative b
{
    long long result = 1 ;
    for( ; b > 0 ; --b ) result *= a ;
    return result ;
}

int pow_mod_n( int a, int b ) { return pow(a,b) % N ; }

int f_mod_n( int a, int b ) { return ( pow_mod_n(a,b) + pow_mod_n(b,a) ) % N ; }

int main()
{
     int sum = 0 ;
     for( int n = 1 ; n < 16 ; ++n ) sum += f_mod_n( n, n+1 ) ;
     std::cout << sum % N << '\n' ;
}
