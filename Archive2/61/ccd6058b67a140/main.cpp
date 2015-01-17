#include <cstdio>
#include <cerrno>

int main()
{
    unsigned int u = 77 ;
    
    std::puts( "std::scanf %u" ) ;
    std::scanf( "%u", &u ) ;
    
    if( errno == 0 ) std::printf( "success: value %u was read\n", u ) ; 
    else if( errno == ERANGE ) std::printf( "input failure: out of range. value was set to %u\n", u ) ;
    else std::puts( "unknown input failure" ) ;
}