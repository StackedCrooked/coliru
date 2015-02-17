#include <iostream>
#include <stdexcept>
#include <cassert>

template < typename T > struct bounded_range
{

    constexpr bounded_range( const T& lb, const T& ub, const T& v = T() )
        : lbound(lb), ubound(ub), value( checked(v) ) {}

    constexpr operator const T& () const { return value ; }

    bounded_range<T>& operator= ( const T& v ) { value = checked(v) ; return *this ; }

    // operator ++ etc.

    bounded_range<T>& reset( const T& lb, const T& ub )
    { lbound = lb ; ubound = ub ; checked(value) ; return *this ; }

    bounded_range<T>& reset( const T& lb, const T& ub, const T& v )
    { lbound = lb ; ubound = ub ; value = checked(v) ; return *this ; }

    private:
        T lbound ;
        T ubound ;
        T value ;

        constexpr const T& checked( const T& v )
        { return v < lbound || v >= ubound ? ( assert(false), throw std::out_of_range("out of range"), v ) : v ; }
};

using brint = bounded_range<int> ;

int main()
{
    try
    {
        brint i( 10, 20, 15 ) ;
        std::cout << i << '\n' ;
        i = i + 3 ;
        std::cout << i << '\n' ;
        i = i + 2 ;
        std::cout << i << '\n' ;
    }
    catch( const std::out_of_range& ) { std::cerr << "out of range\n" ; }

    try { brint j( 10, 20, 25 ) ; std::cout << j << '\n' ; }
    catch( const std::out_of_range& ) { std::cerr << "out of range\n" ; }

}
