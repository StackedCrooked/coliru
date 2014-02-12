#include <stdio.h>

int main()
{
    // read integer from a specified line in text file
    int line_number = 23 ; // first line is line number 1
    
    printf( "try to read integer from line %d of file " __FILE__ "\n", line_number ) ; 
    FILE* file = fopen( __FILE__, "r" ) ;
    
    int ch ;
    while( line_number > 1 && ( ch = fgetc(file) ) != EOF )
        if( ch == '\n' ) --line_number ; // skip till we reach the required line
        
    int number ;
    int result = fscanf( file, "%d", &number ) ;
    if( result != 0 && result != EOF ) printf( "number %d was read\n", number ) ;
}

/*
    12345
    67
    8901
    2345
    67890
    123
*/
