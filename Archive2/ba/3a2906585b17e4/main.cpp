#ifdef INCLUDE_IOSTREAM
#   include <iostream>
#endif
#include <stdio.h>      // ::snprintf
#include <stdlib.h>     // EXIT_SUCCESS, EXIT_FAILURE
#include <stdexcept>    // std::exception

#ifdef snprintf
#   error snprintf defined as macro
#endif

#ifdef _MSC_VER
    auto const snprintf = _snprintf;
#endif

void test( double const value, int const precision)
{
    char buffer[34];
    snprintf( buffer, sizeof( buffer ), "%.*a", precision, value );
    printf( "Hex of %.3f with %2d digits: %s\n", value, precision, buffer );
}

auto main() -> int
{
    using namespace std;
    try
    {
        for( int precision = 6; precision <= 8; ++precision )
        {
            test( 5.0, precision );
        }
        test( 0.0, 14 );
        return EXIT_SUCCESS;
    }
    catch( exception const& x )
    {
        fprintf( stderr, "!%s\n", x.what() );
    }
    return EXIT_FAILURE;
}
