#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    std::vector<int> values_to_play { 0, 1, 2, 3, 4, 5 };

    // option one: range based for
    std::cout << "size: " << values_to_play.size() << "    values: [ " ;
    for( int v : values_to_play ) std::cout << v << ' ' ;
    std::cout << "]\n" ;

    // option two: iterate using positions
    std::cout << "size: " << values_to_play.size() << "    values: [ " ;
    for( std::size_t i = 0 ; i < values_to_play.size() ; ++i ) std::cout << values_to_play[i] << ' ' ;
    std::cout << "]\n" ;

    // option three: iterator
    std::cout << "size: " << values_to_play.size() << "    values: [ " ;
    for( auto iter = values_to_play.begin() ; iter != values_to_play.end() ; ++iter ) std::cout << *iter << ' ' ;
    std::cout << "]\n" ;

    // option four: std::for_each with a callable object
    std::cout << "size: " << values_to_play.size() << "    values: [ " ;
    std::for_each( values_to_play.begin(), values_to_play.end(), []( int v ) { std::cout << v << ' ' ; } ) ;
    std::cout << "]\n" ;

    // option five: std::copy with an output stream iterator
    std::cout << "size: " << values_to_play.size() << "    values: [ " ;
    std::copy( values_to_play.begin(), values_to_play.end(), std::ostream_iterator<int>( std::cout, " " ) ) ;
    std::cout << "]\n" ;
}
