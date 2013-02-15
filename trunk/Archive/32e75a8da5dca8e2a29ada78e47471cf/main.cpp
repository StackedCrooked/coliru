#include <stdio.h>
int main( int argc, const char* argv[] )
{
   // Prints each argument on the command line.
    for( int i = 0; i < argc; i++ )
	{
		printf( "arg %d: %s\n", i, argv[i] );
	}
}