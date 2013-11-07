#include <iostream>
#include <iomanip>

int main()
{
    constexpr std::size_t NROWS = 2 ;
    constexpr std::size_t NCOLS = 3 ;
    const auto setw = std::setw(10) ; // feld width

    const int bertha [NROWS][NCOLS] = {{2,3,4},{7,8,9}} ;

    const char row_label_prefix[] = "Player" ;
    const char col_label_prefix[] = "Round" ;
    int row_total[NROWS] = {0} ;
    int col_total[NCOLS] = {0} ;

    // print col labels
    std::cout << setw << '.' ;
    for( std::size_t column = 0; column < NCOLS ; ++column )
        std::cout << setw << col_label_prefix << column ;
    std::cout << setw << "total" << "\n\n" ;

    for( std::size_t row = 0; row < NROWS ; ++row )
    {
        // print row label
        std::cout << setw << row_label_prefix << row ;

        for( std::size_t column = 0; column < NCOLS ; ++column )
        {
            const int value = bertha [row][column] ;
            std::cout << setw << value << ' ' ;
            row_total[row] += value ;
            col_total[column] += value ;
        }

        // print the row total
        std::cout << setw << row_total[row] << '\n' ;
    }

    // print col totals
    std::cout << '\n' << setw << "total" ;
    for( std::size_t column = 0; column < NCOLS ; ++column )
        std::cout << std::setw(11) << col_total[column] ;
    std::cout << '\n' ;
}
