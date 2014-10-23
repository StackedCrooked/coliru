#include <stdlib.h>

int main( int argc, char* argv[] )
{
    if( argc > 0 ) return main( argc-1, argv+1 ) ;
    else return 0 ;
}
