#include <iostream>

int main()
{
    const int NROWS = 3, NCOLS = 5 ;

    int a[NROWS][NCOLS] = { { 0, 1, 2, 3, 4, }, { 5, 2, 6, 4, 7 }, { 6, 7, 5, 8, 4 } };

    for( int i = 0 ; i < NROWS*NCOLS ; ++i )
    {
        const int row = i / NCOLS ;
        const int col = i % NCOLS ;

        for( int j = i+1 ; j < NROWS*NCOLS ; ++j )
        {
            const int row2 = j / NCOLS ;
            const int col2 = j % NCOLS ;
            
            if( a[row][col] == a[row2][col2] )
                std::cout << "a[" << row << "][" << col << "]  " << a[row][col]
                           << "  a[" << row2 << "][" << col2 << "]\n" ;
        }
    }
}
