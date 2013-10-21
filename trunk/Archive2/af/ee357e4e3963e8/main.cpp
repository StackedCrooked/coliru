#include <iostream>
#include <functional>

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

int main()
{
    utility u ;

    struct other_class
    {
        void my_function() { std::cout << "other_class::my_function(" << this << ")\n" ; }
        int another_function( int a ) const
        {
            std::cout << "other_class::another_function(" << this << ',' << a << ")\n" ;
            return a*a ;
        }
    };

    other_class object ;
    std::cout << "address of object: " << &object << '\n' ;

    u.some_function( 1, 2, &other_class::my_function, &object ) ;
    u.some_function( 3, 4, &other_class::another_function, &object, -7 ) ;
}
