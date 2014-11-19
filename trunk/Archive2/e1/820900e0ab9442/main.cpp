#include <iostream>
#include <type_traits>

template < std::size_t ROWS, std::size_t COLS > // invariant: ROWS > 2, COLS > 2
std::pair<int,int> counts( const int (&array)[ROWS][COLS], std::size_t row, std::size_t col ) // invariant row in [2...ROWS-2],
{
    // invariant row in [1...ROWS-2], col in [1...COLS-2]
    int cnt_high = 0 ;
    int cnt_low = 0 ;

    for( int i : { -1, 0, 1 } ) for( int j : { -1, 0, 1 } )
    {
        cnt_high += array[row+i][col+j] > array[row][col] ;
        cnt_low += array[row+i][col+j] < array[row][col] ;
    }

    return { cnt_high, cnt_low } ;
}

template < std::size_t ROWS, std::size_t COLS >
void peaks_and_valleys( const int (&array)[ROWS][COLS] )
{
    for( std::size_t row = 1 ; row < (ROWS-1) ; ++row )
        for( std::size_t col = 1 ; col < (COLS-1) ; ++col )
        {
            const auto cnts = counts( array, row, col ) ;
            if( cnts.first == 8 ) // cnt_high
                std::cout << "valley " << array[row][col] << " at " << row << "," << col << '\n' ;
            else if( cnts.second == 8 ) // cnt_low
                std::cout << "peak   " << array[row][col] << " at " << row << "," << col << '\n' ;
        }
}

int main()
{
    const int a[][8] =
    {
        { 25, 58, 63, 23, 21, 34, 21, 50 },
        { 32, 45, 43, 40, 41, 32, 30, 27 },
        { 34, 40, 38, 39, 36, 28, 30, 35 },
        { 40, 45, 42, 48, 32, 34, 29, 32 },
        { 39, 39, 40, 42, 47, 49, 27, 30 },
        { 31, 31, 31, 32, 32, 33, 44, 35 }
    };
    peaks_and_valleys(a) ;
}
