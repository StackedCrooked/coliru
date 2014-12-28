#include <stdio.h>

int equals( const char* a, const char* b )
{
    if( a == NULL || b == NULL ) return a == NULL && b == NULL ; // equal if both are NULL

    // invariant a and b are both non-NULL
    for( ; *a && *b ; ++a, ++b ) if( *a != *b ) return 0 ; // not equal if there is a mismatch

    // invariant: all characters up to the end of either one of the two strings are equal
    return *a == 0 && *b == 0 ; // equal if we have reached the end of both strings
}

int main()
{
    const char expected_username[] = "jane1234" ;

    enum { MAX_USERNAME_SZ = 99 } ; // avoid magic numbers
    char username[ MAX_USERNAME_SZ + 1 ] = "" ; // +1 for the terminating null character

    char format[32] = "" ; // avoid magic numbers in the format string too
    sprintf( format, "%%%us", MAX_USERNAME_SZ ) ; // writing maintainable code in C is hard 

    int fields_read = scanf( format, username ) ; // **** not &user_name ****

    if( fields_read == 1 ) 
    {
        printf( "%s: ", username ) ;
        if( equals( username, expected_username ) ) puts( "correct" ) ;
        else puts( "incorrect" ) ;
    }
}
