#include <iostream>

template < typename T, std::size_t N > struct checked_array
{
    T a[N] {} ;

    T& operator[] ( std::size_t pos )
    {
        if( pos >= N ) throw "std::out_of_range" ;
        return a[pos] ;
    }

    const T& operator[] ( std::size_t pos ) const
    {
        if( pos >= N ) throw "std::out_of_range" ;
        return a[pos] ;
    }
};

template < std::size_t FROM, std::size_t TILL, typename FN >
struct unroll_loop
{
    unroll_loop( FN fn = FN() ) { fn(FROM) ; unroll_loop< FROM+1, TILL, FN >{fn} ; }
};

template < std::size_t N, typename FN >
struct unroll_loop< N, N, FN >
{
    unroll_loop( FN ) {}
} ;

struct foo
{
    void operator() ( int i ) const { std::cout << "foo(" << i << ")\n" ; }
};

int main()
{
    unroll_loop<1,6,foo>() ;
    
    checked_array<int,10> a ;
    
    try
    {
        std::cout << a[5] << " fine\n" ;
        std::cout << a[25] ;
    }
    catch( const char* what ) { std::cerr << what << '\n' ; }
}
