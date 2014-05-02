#include <iostream>
#include <iomanip>
#include <numeric>
#include <iterator>

const int COLS = 5 ; 
void fill( int ar[][COLS], int size )
{
    int n = 0 ;
    for( int i = 0 ; i < size ; ++i )
        for( int j = 0 ; j < COLS ; ++j ) ar[i][j] = ++n ;
}

void print( const int ar[][COLS], int size )
{
    for( int i = 0 ; i < size ; ++i )
    {
        for( int j = 0 ; j < COLS ; ++j ) 
            std::cout << std::setw(3) << ar[i][j] << ' ' ;
            
        std::cout << '\n' ;
    }
}

int main()
{
    {
        int a[5][COLS] ;
        fill( a, 5 ) ;
        print( a, 5 ) ;
    }
    std::cout << "-------\n" ;
    
    {
        int b[5][COLS] ;
        int n = 0 ;
        for( auto& row : b ) for( int& i : row ) i = ++n ;
        for( const auto& row : b ) 
        { 
            for( int i : row ) std::cout << std::setw(3) << i << ' ' ;
            std::cout << '\n' ;
        }
    }
    std::cout << "-------\n" ;
    
    {
        int c[5][COLS] ;
        std::iota( std::begin( c[0] ), std::end( c[COLS-1] ), 1 ) ;
        for( const auto& row : c ) 
        { 
            for( int i : row ) std::cout << std::setw(3) << i << ' ' ;
            std::cout << '\n' ;
        }
    }
    std::cout << "-------\n" ;
}
