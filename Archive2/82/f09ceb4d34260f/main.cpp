#include <iostream>
#include <functional>
#include <cstdio>

struct utility
{
    template< typename FUNCTION, typename... ARGS >
    void some_function( int a, int b, FUNCTION custom_function, ARGS... args )
    {
        if( a < b )
        {
            // call custom function
            const auto fn = std::bind( custom_function, args... ) ;
            fn() ;
        }
    }
};

struct foo
{
    void operator() ( int x, double y ) const
    { std::cout << "foo::operator() (" << x << ',' << y << ")\n" ; }
};

int main()
{
    utility u ;

    u.some_function( 1, 2, std::puts, "hello world!" ) ;

    u.some_function( 3, 4, [] { std::cout << "main::anonymous_lambda\n" ; } ) ;

    u.some_function( 5, 6, foo{}, 12345, 67.89 ) ;
}
