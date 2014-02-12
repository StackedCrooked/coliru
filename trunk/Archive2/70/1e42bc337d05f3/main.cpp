#include <string.h>
#include <stdio.h>

int main()
{ 
    {
        enum { MAXSZ = 1024 } ;
        char input[MAXSZ] = "" ;
        
        puts( "please enter a string with spaces in it:" ) ;
        
        // http://www.cplusplus.com/reference/cstdio/fgets/
        if( fgets( input, MAXSZ, stdin ) )
        {
            // knock off the newline character appended at the end
            size_t len = strlen(input) ;
            input[len-1] = 0 ;
            
            printf( "you entered: '%s'\n", input ) ;
        }
    }
}
