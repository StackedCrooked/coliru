#include <iostream>

constexpr int gcd( int a, int b ) { return  a<b ? gcd(b,a) : b ? gcd( b, a%b ) : a ; }

constexpr int lcm( int a, int b ) { return a * b / gcd( a, b ) ; }

constexpr int sum_first_m_multiples_of_n( int n, int m ) { return n * m * (m+1) / 2 ; }

constexpr int sum_multiples_of_n_lt_m( int m, int n )
{ return sum_first_m_multiples_of_n( n, (m-1)/n ) ; }

constexpr int sum_multiples_of_a_or_b_lt_m( int m, int a, int b )
{
    return sum_multiples_of_n_lt_m(m,a) + sum_multiples_of_n_lt_m(m,b) -
            sum_multiples_of_n_lt_m( m, lcm(a,b) ) ;
}

int main()
{
    {
        // sum of all the multiples of 3 or 5 below 1000.
        constexpr int M = 1000 ;
        constexpr int A = 3 ;
        constexpr int B = 5 ;

        using answer_type = char[ sum_multiples_of_a_or_b_lt_m( M, A, B ) ] ;

        std::cout << sizeof(answer_type)  << '\n' ;
    }

    {
        // sum of all the multiples of 21 or 35 below 5000.
        constexpr int M = 5000 ;
        constexpr int A = 21 ;
        constexpr int B = 35 ;

        using answer_type = char[ sum_multiples_of_a_or_b_lt_m( M, A, B ) ] ;

        std::cout << sizeof(answer_type)  << '\n' ;
    }
}
