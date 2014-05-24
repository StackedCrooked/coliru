#include <iostream>

int main()
{
    const int NUM_ROWS = 6 ;
    
    for( int row = 1 ; row <= NUM_ROWS ; ++row ) // for each row 1 .. NUM_ROWS
    {
        // print numbers row, row+1 ... (row times) 
        for( int col = 0 ; col < row ; ++col )
        {
            std::cout << row+col << ' ' ;
        }
        
        std::cout << '\n' ; // and a new line at the end of each row
    }
}
