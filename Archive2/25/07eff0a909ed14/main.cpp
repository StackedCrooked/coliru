#include <new>

struct A { A( int a, int b ) : aval(a), bval(b) {} int aval ; int bval ; };

A* construct( void* here, const A& v ) { return new(here) A(v) ; }

A* foo( char* buffer, int a, int b )
{
    A temp( a, b ) ;
    A* p = buffer ? construct( buffer, temp ) : 0 ;
    return p ; 
}
