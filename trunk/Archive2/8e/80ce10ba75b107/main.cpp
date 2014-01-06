#pragma GCC diagnostic push
// save the current state for diagnostics

#pragma GCC diagnostic ignored "-Wunused-parameter"
// turn off diagnostic for "-Wunused-parameter"  

#include "some_header.h"

// note: some_header.h contains: 
// template < typename T > int foo( T arg_foo ) { return 0 ; }

// some_header.h is shared at: http://coliru.stacked-crooked.com/a/517f2af527f417cc 
// see command line: ln -s /Archive2/51/7f2af527f417cc/main.cpp some_header.h

#pragma GCC diagnostic pop
// restores the saved state for diagnostics (diagnostics as specified in the command line)  

template < typename T > int bar( T arg_bar ) { return 0 ; }

int main()
{
    foo(100) ; 

    bar(100) ; // *** warning: unused parameter 'arg_bar' [-Wunused-parameter]|
}
