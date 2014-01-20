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

int main()
{
     // 58 to be placed before anything else,
     // 11 to be placed after everything else,
     // order on ascending last digit,
     // except that last digit 7 appears before other last digits,
     // if last digits are equal, order by decreasing value
     const auto cmp = compose<int>
     (
         [] ( int a, int b ) { return a == 58 && b != 58 ; },
         [] ( int a, int b ) { return a != 11 && b == 11 ; },
         [] ( int a, int b ) { return a%10 == 7 && b%10 != 7 ; },
         [] ( int a, int b ) { return a%10 < b%10 ; },
         [] ( int a, int b ) { return a > b ; }
     ) ;

     int a[] = { 19, 22, 11, 25, 11, 58, 77, 32, 58, 45, 16, 77, 39, 83, 95, 98, 17 } ;

     std::sort( std::begin(a), std::end(a), cmp ) ;
     for( int v : a ) std::cout << v << ' ' ;
     std::cout << '\n' ;
}
