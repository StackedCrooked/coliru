#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <algorithm>
#include <iterator>
#include <numeric>

template< typename SEQ >
std::vector<std::size_t> shuffled_positions( const SEQ& seq )
{
    std::vector<std::size_t> v( seq.size() ) ;
	std::iota( std::begin(v), std::end(v), 0 ) ;
    std::random_shuffle( std::begin(v), std::end(v) ) ;
	return v ;
}

template < typename CALLABLE, typename... ARGS >
void random_if_else_if( const std::vector<CALLABLE>& predicate_and_action, ARGS&&... args  )
{
    for( auto pos : shuffled_positions(predicate_and_action) )
		if( predicate_and_action[pos]( args... ) ) break;
}

int main()
{
    std::srand( std::time (nullptr) ) ;

    std::vector< std::function< bool(int) > > predicate_and_action =
    {
        []( int v )->bool { return v%2 ? std::cout << "odd\n" : false ; },
        []( int v )->bool { return v%2==0? std::cout << "even\n" : false ; },
        []( int v )->bool { return v%3==0 ? std::cout << "divisible by 3\n" : false ; },
        []( int v )->bool { return v%5==0 ? std::cout << "divisible by 5\n" : false ; },
        []( int v )->bool { return v%6==0 ? std::cout << "divisible by 6\n" : false ; }
    };

    for( int i = 0 ; i < 15 ; ++i ) random_if_else_if( predicate_and_action, i ) ;
    std::cout << "----------------------\n" ;

    predicate_and_action.insert( predicate_and_action.end(),
    {
        []( int v )->bool { return v < 10 ? std::cout << "less than 10\n" : false ; },
        []( int v )->bool { return v < 15 ? std::cout << "less than 15\n" : false ; },
        []( int v )->bool { return v < 20 ? std::cout << "less than 20\n" : false ; },
    } );

    for( int i = 0 ; i < 15 ; ++i ) random_if_else_if( predicate_and_action, i ) ;
}
