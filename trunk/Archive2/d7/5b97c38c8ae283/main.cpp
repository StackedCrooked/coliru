#include <iostream>

int print_terms_and_sum_up( int nterms, int a = 1, int b = 1, int cnt = 0, int sum_so_far = 0 )
{
    if( cnt < nterms )
    {
        std::cout << ( cnt ? ", " : "" ) << a+b ;
        return print_terms_and_sum_up( nterms, b, a+b, cnt+1, sum_so_far + a+b ) ;
    }

    else return sum_so_far ;
}

int main() 
{ 
    int n = 15 ;
    int sum = print_terms_and_sum_up(n) ;
    std::cout << "\nsum == " << sum << '\n' ;
}
