#include <iostream>
#include <bitset>
#include <string>

constexpr std::size_t N = 3 ;

namespace tictactoe
{
    using board = std::bitset<N*N> ;
    const board wins[] = {
                             board("111000000"), board("000111000"), board("000000111"), // rows
                             board("100100100"), board("010010010"), board("001001001"), // cols
                             board("100010001"), board("001010100") // diagonals
                         } ;
    board noughts ;
    board crosses ;
    static constexpr char NOUGHT = 'O' ;
    static constexpr char CROSS = 'X' ;
    bool curr_move_noughts = true ;

    board combined() { return noughts | crosses ; }

    bool valid( std::size_t row, std::size_t col ) { return row<N && col<N ; }
    std::size_t pos( std::size_t row, std::size_t col ) { return row*N + col ; }

    bool occupied( std::size_t row, std::size_t col ) { return valid(row,col) && combined()[ pos(row,col) ] ; }
    bool free( std::size_t row, std::size_t col ) { return valid(row,col) && !occupied(row,col) ; }

    void make_move( std::size_t row, std::size_t col, board& b ) { if( free(row,col) ) b[ pos(row,col) ] = true ; }
    void make_move( std::size_t row, std::size_t col )
    { if(curr_move_noughts) make_move(row,col,noughts) ; else make_move(row,col,crosses) ; }

    bool is_win( board b )
    {
        for( board w : wins ) if( (w&b) == w ) return true ;
        return false ;
    }
    bool is_win() { return is_win( curr_move_noughts ? noughts : crosses ) ; }

    std::ostream& print_board( std::ostream& stm = std::cout, board b = combined() )
    {
        stm << "------\n" ;
        for( std::size_t i = 0 ; i < N ; ++i )
        {
            for( std::size_t j = 0 ; j < N ; ++j )
            {
                const std::size_t k = pos(i,j) ;
                if( b[k] ) stm << ( noughts[k] ? NOUGHT : CROSS ) << ' ' ;
                else stm << ". " ;
            }
            stm << '\n' ;
        }
        return stm << "------\n" ;
    }
}

int main()
{
    using namespace tictactoe ;

    make_move(1,2) ;
    print_board() ;
    curr_move_noughts = !curr_move_noughts ;

    // for testing: let the same player make three consecutive moves
    make_move(2,0) ; make_move(1,1) ; make_move(0,2) ;
    print_board() ;
    std::cout << "win? " << std::boolalpha << is_win() << '\n' ;
}
