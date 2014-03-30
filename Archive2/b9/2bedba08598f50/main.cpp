#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const std::size_t N = 15 ;
enum orientation { UP, DOWN, LEFT, RIGHT };
const char empty = '.' ;

bool try_place_ship( char (&board) [N][N], std::size_t x, std::size_t y,
                      std::size_t x1, std::size_t y1, char bow, char stern )
{
    if( board[x][y] == empty && board[x1][y1] == empty )
    {
        board[x][y] = bow ;
        board[x1][y1] = stern ;
        return true ;
    }

    return false ;
}

void place_ship( char (&board) [N][N] )
{
    bool placed = false ;

    while( !placed )
    {
        switch( std::rand() % 4 ) // choose a random orientation
        {
            case UP: // bow in rows [0, N-2]
            {
                std::size_t row = std::rand() % (N-1) ;
                std::size_t col = std::rand() % N ;
                placed = try_place_ship( board, row, col, row+1, col, '^', '|' ) ;
            }
                break ;

            case DOWN: // bow in rows [1, N-1]
            {
                std::size_t row = std::rand() % (N-1) + 1 ;
                std::size_t col = std::rand() % N ;
                placed = try_place_ship( board, row, col, row-1, col, 'v', '|' ) ;
            }
                break ;

            case LEFT: // bow in cols [0, N-2]
            {
                std::size_t row = std::rand() % N ;
                std::size_t col = std::rand() % (N-1) ;
                placed = try_place_ship( board, row, col, row, col+1, '<', '-' ) ;
            }
                break ;

            case RIGHT: // bow in cols [1, N-1]
            {
                std::size_t row = std::rand() % N ;
                std::size_t col = std::rand() % (N-1) + 1 ;
                placed = try_place_ship( board, row, col, row, col-1, '>', '-' ) ;
            }
                break ;
        }
    }
}

int main()
{
    std::srand( std::time(nullptr) ) ;

    char board[N][N] ;
    for( auto& row : board ) for( char& c : row ) c = empty ; // empty

    // place 12 ships randomly
    for( int i = 0 ; i < 20 ; ++i ) place_ship(board) ;

    for( auto& row : board )
    {
        for( char c : row ) std::cout << c ;
        std::cout << '\n' ;
    }
}
