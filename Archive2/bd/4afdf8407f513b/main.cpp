#include <stdio.h>

unsigned int plus( unsigned int a, unsigned int b ) { return a + b ; }
unsigned int bit_and( unsigned int a, unsigned int b ) { return a & b ; }
unsigned int bit_shift_left( unsigned int a, unsigned int b ) { return a << b ; }

const char operators[] = { '+', '&', '<' } ;
enum { N = sizeof(operators) };
const char* const operator_names[] = { "plus", "bit-and", "bit-shift-left" } ;

typedef unsigned int operation( unsigned int, unsigned int ) ;
operation* operations[] = { plus, bit_and, bit_shift_left } ;

int pos( char operator )
{
    for( int p = 0 ; p < N ; ++p ) if( operators[p] == operator ) return p ;
    return -1 ;
}

const char* name( char operator ) { int p = pos(operator) ; return p != -1 ? operator_names[p] : "" ; }
operation* function( char operator ) { int p = pos(operator) ; return p != -1 ? operations[p] : NULL ; }

void print_operation( unsigned int n, unsigned int m, char oper )
{
    operation*  fn = function(oper) ;
    if( fn != NULL ) printf( "%s: %u %c %u == %u\n", name(oper), n, oper, m, fn(n,m) ) ;
    else printf( "unsupported operation '%c'\n", oper ) ;
}

int main()
{
    print_operation( 22, 87, '+' ) ;
    print_operation( 16, 3, '<' ) ;
    print_operation( 25, 19, '&' ) ;
    
}
