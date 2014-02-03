#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    size_t sz = 20 ;
    char* number = (char*)malloc(20) ;
    if( number == NULL ) return 1 ;

    puts( "please type in the number: " ) ;

    int c ;
    // skip over leading white space
    while( ( c = getchar() ) != EOF )
    {
        if( !isspace(c) )
        {
            ungetc( c, stdin ) ;
            break ;
        }
    }

    size_t pos = 0 ;
    // keep going till we hit EOF or a non-digit character is entered
    while( ( c = getchar() ) != EOF )
    {
        if( c == '\n' ) continue ; // new line, user wants to enter more digits,
                                    // go on to get the next digit

        if( !isdigit(c) ) break ; // a non-digit character is entered,
                                   // there are no more digits

        number[pos] = c ; // c holds a digit

        if( pos == sz-1 ) // if we have run out of space
        {
            // resize the buffer
            sz *= 2 ; // use a canonical doubling strategy

            // try to reallocate to the bigger buffer
            char* temp = (char*)realloc( number, sz ) ;
            if( temp == NULL )
            {
               free(number) ;
               return 1 ;
            }
            else number = temp ;
        }
        ++pos ;
    }

    number[pos] = 0 ; // null terminate

    printf( "The number is: %s\n", number ) ;

    // TODO: check if it is a palindrome

    // check if digit at positiion 0 is the same as digit at position pos-1,
    // check if digit at positiion 1 is the same as digit at position pos-2,
    // till the middle digit is reached

    // print out the result of the check


    free(number) ;
}
