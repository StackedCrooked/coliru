#include <stdio.h>

class X
{
public:
    X( int x ){ printf( "%d\n", x ); }

    X( char const* )
        : X( 42 )
    {}
};

auto main() -> int
{
    X x( "blah blah" );
}
