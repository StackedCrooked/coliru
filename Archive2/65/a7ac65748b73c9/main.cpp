#include <stdio.h>
#include <errno.h>

int main()
{
    unsigned int u = 77 ;
    
    puts( "scanf %u" ) ;
    scanf( "%u", &u ) ;
    
    if( errno == 0 ) printf( "success: value %u was read\n", u ) ; 
    else if( errno == ERANGE ) printf( "input failure: out of range. value was set to %u\n", u ) ;
    else puts( "unknown input failure" ) ;
}
