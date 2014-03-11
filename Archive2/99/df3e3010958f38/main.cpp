// -*- C Password Program -*-
// deprecated

#include <stdio.h> // printf()
#include <conio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    const char* password = "abcdef";

    char szInput[ 32 ] = { 0 }; // max input is 32

    int i = 0;
    char c;
    do {
        c = getch();

        if( c == '\b' ) {
            printf( "\b \b" );
            if( i != 0 ) {
                szInput[ --i ] = 0;
            }
        } else if( isprint(c) ) {
            printf( "*" );
            szInput[ i++ ] = c;
        }
    } while( (c != '\r') and (i != 32) );

    if( strcmp( szInput, password ) == 0 ) {
        printf( "\nAccess Granted\n" );
    } else {
        printf( "\nAccess Denied\n" );
    }
}
