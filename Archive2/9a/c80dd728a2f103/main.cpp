template < typename T, typename... PREDICATE > struct predicate_builder ;

template < typename T, typename PREDICATE > struct predicate_builder<T,PREDICATE>
{
    predicate_builder( PREDICATE fn ) : cmp(fn) {}

    bool operator() ( T a, T b ) const { return cmp(a,b) ; }

    const PREDICATE cmp ;
};

template < typename T, typename FIRST, typename... REST >
struct predicate_builder<T,FIRST,REST...> : predicate_builder<T,REST...>
{
    using base = predicate_builder<T,REST...> ;

    predicate_builder( FIRST first, REST... rest ) : base(rest...), cmp(first) {}

    bool operator() ( T a, T b ) const
    {
        if( cmp(a,b) ) return true ;
        else if( cmp(b,a) ) return false ;
        else return base::operator() (a,b) ;
    }

    const FIRST cmp ;
};

template< typename T, typename... PREDICATE >
predicate_builder<T,PREDICATE...> compose( PREDICATE... fn )
{ return predicate_builder<T,PREDICATE...>(fn...) ; }

#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>

struct primes_in_groups
{
    bool operator() ( int a, int b ) const
    {
        const bool is_prime_a = is_prime(a) ;
        const bool is_prime_b = is_prime(b) ;

        switch( is_prime_a + is_prime_b )
        {
            case 0 : return false ;
            case 1 : return is_prime_a ;
            default : // both are prime numbers
                if( a/10 == b/10 ) return a > b ;
                else return a/10 < b/10 ;
        }
    }

    static bool is_prime( int n )
    {
        if( n < 2 ) return false ;
        if( n == 2 ) return true ;
        if( n%2 == 0 ) return false ;
        int ubsqrt = std::sqrt(n) + 2 ;
        for( int i = 3 ; i < ubsqrt ; i += 2 ) if( n%i == 0 ) return false ;
        return true ;
    }
};

int main()
{
    // 25 placed first before anything else
    // 16 to be placed after everything else,
    // even numbers placed after all 25's, if any, have been placed
    // (and the even numbers sorted in increasing value among themselves)
    // prime numbers then placed in groups in the order 1-9, 10-19, 20-29, 30-39, 40-49 (and in decreasing value within each group)
	// after these order on ascending last digit,
    // except that last digit 7 appears before other last digits,
    // if last digits are equal, order by increasing value

    const auto even_numbers = [] ( int a, int b )
    {
        if( a%2 == 0 && b%2 == 0 ) return a<b ;
        else return a%2 == 0 && b%2 != 0 ;
    };

    const auto comp = compose<int>
    (
     	[] (int a, int b) {return a == 25 && b != 25;},
        [] (int a, int b) {return a != 16 && b == 16;},
        even_numbers,
        primes_in_groups(),
        [] (int a, int b) {return a%10 == 7 && b%10 != 7;},
        [] (int a, int b) {return a%10 < b%10;},
        [] (int a, int b) {return a < b;}
    );

    int a[] = { 19, 22, 11, 23, 25, 31, 40, 37, 32, 35, 45, 21, 33, 21, 38, 25, 47, 27, 16,
                47, 39, 16, 25, 5, 7, 35, 48, 17, 27, 57, 31, 29, 23, 43, 17, 41, 3, 7, 13 };

    std::sort (std::begin (a), std::end (a), comp ) ;
    for( int v : a ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
