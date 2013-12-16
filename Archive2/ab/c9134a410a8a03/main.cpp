#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <array>

template< typename SEQ >
std::vector<std::size_t> shuffled_positions( const SEQ& seq )
{
    std::vector<std::size_t> v( seq.size() ) ;
	std::iota( std::begin(v), std::end(v), 0 ) ;
    std::random_shuffle( std::begin(v), std::end(v) ) ;
	return v ;
}

template< std::size_t N > std::array< std::size_t, N >& shuffled_positions()
{
	static std::array< std::size_t, N > positions ;
	static int not_used = ( std::iota( std::begin(positions), std::end(positions), 0 ), 0 ) ;
    std::random_shuffle( std::begin(positions), std::end(positions) ) ;
	return positions ;
}

template < typename CALLABLE, typename... ARGS >
void random_if_else_if( const std::vector<CALLABLE>& predicate_and_action, ARGS&&... args  )
{
    for( auto pos : shuffled_positions(predicate_and_action) )
		if( predicate_and_action[pos]( args... ) ) break;
}

template < std::size_t N, typename CALLABLE, typename... ARGS >
void random_if_else_if( const std::array<CALLABLE,N>& predicate_and_action, ARGS&&... args  )
{
    for( auto pos : shuffled_positions<N>() )
		if( predicate_and_action[pos]( args... ) ) break;
}

template < std::size_t N, typename CALLABLE, typename... ARGS >
void random_if_else_if( CALLABLE (&predicate_and_action)[N], ARGS&&... args  )
{
    for( auto pos : shuffled_positions<N>() )
		if( predicate_and_action[pos]( args... ) ) break;
}

int main()
{
    std::srand( std::time (nullptr) ) ;

    const std::function< bool(int) > const_if_else_if[] =
    {
        []( int v )->bool { return v%2 ? std::cout << "odd\n" : false ; },
        []( int v )->bool { return v%2==0? std::cout << "even\n" : false ; },
        []( int v )->bool { return v%3==0 ? std::cout << "divisible by 3\n" : false ; },
        []( int v )->bool { return v%5==0 ? std::cout << "divisible by 5\n" : false ; },
        []( int v )->bool { return v%6==0 ? std::cout << "divisible by 6\n" : false ; }
    };

    std::vector< std::function< bool(int) > > if_else_if
    {
        []( int v )->bool { return v < 10 ? std::cout << "less than 10\n" : false ; },
        []( int v )->bool { return v < 15 ? std::cout << "less than 15\n" : false ; },
        []( int v )->bool { return v < 20 ? std::cout << "less than 20\n" : false ; },
    };

    for( int i = 0 ; i < 10 ; ++i )
    {
        std::cout << i << ' ' ;
        random_if_else_if( const_if_else_if, i ) ;
        std::cout << i << ' ' ;
        random_if_else_if( if_else_if, i ) ;
    }
}
