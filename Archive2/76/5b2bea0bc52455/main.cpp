#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
        enum { MAXSZ = 50 };
        int list[MAXSZ] ;
        int sz = 0 ;

        puts( "enter numbers one by one separated by white space; enter a new line to terminate input: " ) ;

        while( sz < MAXSZ )
        {
            int ch ;
            do
            {
                ch = fgetc( stdin );
                if( ch == '\n' || ch == EOF ) goto done ;

            } while( isspace(ch) ) ;

            ungetc( ch, stdin ) ;

            int number ;
            if( scanf( "%d", &number ) != 1 ) break ;

            list[sz] = number ;
            ++sz ;
        }

    done:
        for( int i = 0 ; i < sz ; ++i ) printf( "%d ", list[i] ) ;
        puts( "" ) ;
}
