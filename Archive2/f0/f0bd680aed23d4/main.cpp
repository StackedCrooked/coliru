#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <algorithm>
#include <iterator>

void random_if_else_if( int v )
{
    static const std::function< bool(int) > predicate_and_action[] =
    {
        []( int v )->bool { return v%2 ? std::cout << "odd\n" : false ; },
        []( int v )->bool { return v%2==0? std::cout << "even\n" : false ; },
        []( int v )->bool { return v%3==0 ? std::cout << "divisible by 3\n" : false ; },
        []( int v )->bool { return v%5==0 ? std::cout << "divisible by 5\n" : false ; },
        []( int v )->bool { return v%6==0 ? std::cout << "divisible by 6\n" : false ; },
        []( int v )->bool { return v < 10 ? std::cout << "less than 10\n" : false ; },
        []( int v )->bool { return v < 15 ? std::cout << "less than 15\n" : false ; },
        []( int v )->bool { return v < 20 ? std::cout << "less than 20\n" : false ; },
        []( int v )->bool { return v < 25 ? std::cout << "less than 25\n" : false ; },
        []( int v )->bool { return v < 30 ? std::cout << "less than 30\n" : false ; }
    };

    static std::size_t sequence[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;

    std::random_shuffle( std::begin(sequence), std::end(sequence) ) ;
    for( auto pos : sequence ) if( predicate_and_action[pos](v) ) break ;
}

int main()
{
    std::srand( std::time(nullptr) ) ;

    for( int i = 0 ; i < 20 ; ++i )
    {
        std::cout << i << ' ' ;
        random_if_else_if(i) ;
    }
}
