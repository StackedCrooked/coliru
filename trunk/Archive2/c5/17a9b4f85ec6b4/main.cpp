#include <iostream>

template < int N >
void print_it( int (&a)[N], int from_pos = 0 )
{
    if( from_pos == N )
    {
        for( int v : a ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }

    else
    {
        for( int i = 0 ; i < N ; ++i )
        {
            a[from_pos] = i ;
            print_it( a, from_pos+1 ) ;
        }
    }
}

int main()
{
    int array[3] {} ;
    print_it(array) ;
}
