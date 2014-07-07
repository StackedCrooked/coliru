#include <iostream>
#include <map>
#include <iomanip>

int main()
{
    std::map< std::size_t, std::map< std::size_t, int > > m ;

    m[1][5] = 15 ;
    m[7][2] = 72 ;
    m[3][5] = 35 ;
    m[6][0] = 60 ;
    
    std::cout << "  'x' => no value has been set\n  ----------------------------\n" ;
    
    for( std::size_t row = 0 ; row < 8 ; ++row )
    {
        const auto irow = m.find(row) ;

        for( std::size_t col = 0 ; col < 8 ; ++col )
        {
            if( irow != m.end() ) // if the row has some entries
            {
                const auto icol = irow->second.find(col) ;
                if( icol != irow->second.end() ) // and there is an entry at [row][col]
                    std::cout << std::setw(3) << icol->second << ' ' ;
                else
                    std::cout << "  x " ;
            }
            else std::cout << "  x " ;
        }

        std::cout << '\n' ;
    }
}
