#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <array>

using pos_type = std::pair< std::size_t, std::size_t > ;

// maps position to row, col, diags positions to look up
// the vector lobically contains a sequence of (n-1)-tuples where n == board_size
// where each (n-1)-tuple represents the remaing n-1 positions to look up
using map_type = std::map< pos_type, std::vector<pos_type> > ;

template < std::size_t N > map_type make_map()
{
    map_type m ;

    for( std::size_t row = 0 ; row < N ; ++row )
        for( std::size_t col = 0 ; col < N ; ++col )
        {
            auto& vec = m[ {row,col} ] ;

            // row
            for( std::size_t c = 0 ; c < N ; ++c ) if( c!=col ) vec.emplace_back(row,c) ;

            // col
            for( std::size_t r = 0 ; r < N ; ++r ) if( r!=row ) vec.emplace_back(r,col) ;

            // diaganols
            if( row == col ) for( std::size_t i = 0 ; i < N ; ++i )
                    if( i != row ) vec.emplace_back(i,i) ;

            if( row == N -col-1 ) for( std::size_t i = 0 ; i < N ; ++i )
                    if( i != row ) vec.emplace_back( i, N-i-1 ) ;
        }

     return m ;
}

template< typename BOARD >
bool check_win( const BOARD& board, pos_type last_move,
                const map_type& look_up, std::size_t N )
{
    const auto& v = board[last_move.first][last_move.second] ;
    const std::vector<pos_type>& seq = look_up.find(last_move)->second ;

    // size of row, col diuag == N, so check blocks of N-1 (other positions) at a time
    const std::size_t NLOOKUPS = N-1 ;
    for( auto iter = seq.begin() ; iter < seq.end() ; iter += NLOOKUPS )
    {
        std::size_t cnt = 0 ;
        for( auto subiter = iter ; subiter < iter + NLOOKUPS ; ++subiter )
            if( board[subiter->first][subiter->second] == v ) ++cnt ;
            else break ;
        if( cnt == NLOOKUPS ) return true ; // found row, col or diag with all N == v
    }

    return false ;
}

template< typename BOARD >
bool check_win( const BOARD& board, pos_type last_move, const map_type& look_up )
{ return check_win( board, last_move, look_up, board.size() ) ; }

int main()
{
    constexpr std::size_t BOARD_SZ = 7 ;
    int board[BOARD_SZ][BOARD_SZ] =
    {
        { 0, 1, 0, 5, 0, 0, 5 },
        { 0, 0, 0, 0, 0, 5, 0 },
        { 1, 0, 0, 0, 5, 0, 0 },
        { 0, 1, 0, 5, 1, 0, 1 },
        { 0, 0, 5, 0, 1, 0, 0 },
        { 0, 5, 5, 0, 1, 0, 0 },
        { 5, 0, 0, 0, 1, 0, 0 }
    };

    const map_type look_up = make_map<BOARD_SZ>() ;

    std::cout << std::boolalpha << check_win( board, {2,4}, look_up, BOARD_SZ ) << '\n' ;
}
