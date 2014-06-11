#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <map>
#include <functional>
#include <fstream>
#include <iterator>

// word: sequence of characters without embedded whitespace
//       and without leading or trailing non-alpha characters
//       with all the characters converted to lower case
std::istream& getword( std::istream& stm, std::string& word )
{
    const auto& loc = stm.getloc() ;
    const auto alpha = [&loc]( char c ) { return std::isalpha( c, loc ) ; } ;

    while( stm >> word )
    {
        const auto begin = std::find_if( word.begin(), word.end(), alpha ) ;

        if( begin != word.end() )
        {
            word = { begin, std::find_if( word.rbegin(), word.rend(), alpha ).base() } ;
            for( char& c : word ) c = std::tolower( c, loc ) ;
            return stm ;
        }
    }

    return stm ;
}

std::map< std::string, int > make_word_count( std::istream& stm )
{
    std::map< std::string, int > wc ;

    std::string word ;
    while( getword( stm, word ) )  ++wc[word] ;

    return wc ;
}

template < typename OUTPUT_ITERATOR >
OUTPUT_ITERATOR copy_most_used( const std::map< std::string, int >& wc,
                                OUTPUT_ITERATOR dest, std::size_t n = 5 )
{
    std::multimap< int, std::reference_wrapper<const std::string> > inverted_map ;
    for( const auto& pair : wc )
        inverted_map.emplace( pair.second, std::cref(pair.first) ) ;

    n = std::min( wc.size(), n ) ;
    auto end = inverted_map.rbegin() ;
    std::advance( end, n ) ;
    for( auto iter = inverted_map.rbegin() ; iter != end ; ++iter, ++dest )
        *dest = iter->second ;
    return dest ;
}

int main()
{
    std::ifstream file( __FILE__ ) ;
    const auto word_count = make_word_count(file) ;

    std::cout << "most used words\n--------------\n" ;
    copy_most_used( word_count, std::ostream_iterator<std::string>( std::cout, "\n" ) ) ;
}
