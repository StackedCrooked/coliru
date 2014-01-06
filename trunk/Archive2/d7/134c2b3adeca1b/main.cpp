#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "some_header.h"

#pragma GCC diagnostic pop

template < typename T > int bar( T arg_bar ) { return 0 ; }

int main()
{
    foo(100) ; 

    bar(100) ; // *** warning: unused parameter 'arg_bar' [-Wunused-parameter]|
}
