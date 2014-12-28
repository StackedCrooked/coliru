#include <stdio.h>

int equals( const char* a, const char* b )
{
    if( a == NULL || b == NULL ) return a == NULL && b == NULL ; // equal if both are NULL

    // invariant a and b are both non-NULL
    for( ; *a && *b ; ++a, ++b ) if( *a != *b ) return 0 ; // not equal if there is a mismatch

    // invariant: all characters up to the end of either one of the two strings are equal
    return *a == 0 && *b == 0 ; // true if we have reached the end of both strings
}

int main()
{
    const char expected_username[] = "jane1234" ;

    enum { SZ = 100 } ;
    char username[SZ] = "" ;

    char format[32] = "" ;
    sprintf( format, "%%%us", SZ-1 ) ;

    int fields_read = scanf( format, username ) ; // **** not &user_name

    if( fields_read == 1 && equals( username, expected_username ) ) puts( "correct" ) ;
    else puts( "incorrect" ) ;
}
