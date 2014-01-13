#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* to_string( long value, char* buffer, size_t bufsz, size_t offset )
{
    snprintf( buffer+offset, bufsz-offset, "%ld", value ) ;
    return buffer ;
}

char* to_malloced_string( long value )
{
    enum { SZ = 32 } ;
    char* str = malloc(SZ) ;
    if(!str) return NULL ;
    return to_string( value, str, SZ, 0 ) ;
}

int main()
{
    int v = 12345 ;
    char cstr[128] = "The value is: " ;

    to_string( v, cstr, sizeof(cstr), strlen(cstr) ) ;
    puts(cstr) ;

    char* temp = to_malloced_string(999) ;
    puts(temp) ;
    free(temp) ;
}
