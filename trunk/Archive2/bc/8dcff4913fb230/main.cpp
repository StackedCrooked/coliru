#include <stdio.h>
#include <stdbool.h>

static unsigned int do_reverse_bits_( unsigned int n, unsigned int reversed_so_far )
{ return n ? do_reverse_bits_( n/2, reversed_so_far*2 + n%2 ) : reversed_so_far ; }

unsigned int reverse_bits( unsigned int n ) { return do_reverse_bits_( n, 0 ) ; }

bool is_binary_palindrome( unsigned int n ) { return n == reverse_bits(n) ; }

void print_bits( unsigned int n ) { if( n > 0 ) { print_bits(n/2) ; printf( "%u", n%2 ) ; } }

int main()
{
    const unsigned int numbers[] = { 64575, 1398101, 911, 262015, 2863289685 } ;

    for( unsigned int i = 0 ; i < sizeof(numbers) / sizeof( numbers[0] ) ; ++i )
    {
        const unsigned int n = numbers[i] ;
        printf( "%u is %sa binary palindrome. (", n, is_binary_palindrome(n) ? "" : "not " ) ;
        print_bits(n) ;
        puts( ")" ) ;
    }
}
