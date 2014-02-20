#include <vector>
#include <map>
#include <string>
#include <cctype>
#include <utility>
#include <sstream>
#include <iostream>

using seq_type = std::vector<std::string> ; // sentences

// map word => position in sentences sequence
using map_type = std::multimap< std::string, std::size_t > ;

std::string sanitize( std::string word )
{
    std::string result ;
    for( char c : word ) if( std::isalnum(c) ) result += std::tolower(c) ;
    return result ;
}

std::pair<map_type,seq_type> make_map( std::istream& stm, std::string end_chars = ".?!" )
{
    map_type map ;
    seq_type seq(1) ;

    std::string word ;
    while( stm >> word )
    {
        seq.back() += word ;
        map.emplace( sanitize(word), seq.size() - 1 ) ;

        if( end_chars.find( word.back() ) != std::string::npos ) seq.push_back("") ;
        else seq.back() += ' ' ;
    }

    if( seq.back().empty() ) seq.pop_back() ;
    return { map, seq } ;
}

int main()
{
    std::istringstream file
    ( R"(
        Shall I compare thee to a summer's day? Thou art
        more lovely and more temperate. Rough winds do
        shake the darling buds of May! And summer's lease
        hath all too short a date. Sometime too hot the eye
        of heaven shines. And often is his gold complexion dimm'd!
        And every fair from fair sometime declines. By chance,
        or nature's changing course untrimm'd.
    )" );

    const auto pair = make_map(file) ;
    const map_type& map = pair.first ;
    const seq_type& seq = pair.second ;

    std::cout << "-------   sentences    --------------------\n" ;
    for( std::size_t i = 0 ; i < seq.size() ; ++i )
        std::cout << i << ". " << seq[i] << '\n' ;

    std::cout << "\n-------   look up    --------------------\n" ;
    for( const auto& s : { "lovely", "and", "day!!!", "date", "zebra", "thou", "The" } )
    {
        std::cout << s << '\n' ;
        auto bounds = map.equal_range( sanitize(s) ) ;
        for( auto iter = bounds.first ; iter != bounds.second ; ++iter )
            std::cout << '\t' << iter->second << ". " << seq[iter->second] << '\n' ;
        std::cout << "\n\n" ;
    }
}
