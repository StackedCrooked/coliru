#include <iostream>

void print_terms_and_sum( int nterms, int a = 1, int b = 1, int cnt = 0, int sum_so_far = 0 )
{
    if( cnt < nterms )
    {
        std::cout << ( cnt ? ", " : "" ) << a+b ;
        print_terms_and_sum( nterms, b, a+b, cnt+1, sum_so_far + a+b ) ;
    }
    else std::cout << "\nsum == " << sum_so_far << '\n' ;
}

int main() 
{ 
    int nterms ;
    std::cin >> nterms ;
    print_terms_and_sum(nterms) ;
    
}
