#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <fstream>
#include <iterator>
#include <vector>
#include <locale>
#include <memory>

namespace
{
    std::map< std::string, int > do_make_word_count( std::istream& stm )
    {
        std::map< std::string, int > wc ;
        auto locale = stm.getloc() ;

        std::string word ;
        while( stm >> word )
        {
            for( char& c : word ) c = std::tolower( c, locale ) ;
            ++wc[word] ;
        }

        return wc ;
    }
}

std::map< std::string, int > make_word_count( std::istream& stm )
{
    struct replace_ctype // raii shim
    {
            // This ctype facet classifies all non-alpha as whitespace
            struct non_alpha_is_ws : std::ctype<char>
            {
                static const mask* classification_table()
                {
                    // start with the classic table ( C locale's table )
                    static std::vector<mask> table( classic_table(),  classic_table() + table_size ) ;

                    // all non-alphas are to be treated as whitespace
                    for( std::size_t i = 0 ; i < table_size ; ++i )
                        if( !std::isalpha(i) ) table[i] = space ;

                    return std::addressof( table.front() ) ;
                }

                // do not delete table, initial reference count == 0
                non_alpha_is_ws() : std::ctype<char>( classification_table() ) {}
            };

        replace_ctype( std::istream& stm ) : stm(stm),
            old_locale( stm.imbue( std::locale( stm.getloc(), new non_alpha_is_ws ) ) ) {}
        ~replace_ctype() { stm.imbue(old_locale) ; }

        replace_ctype( const replace_ctype& ) = delete ;
        replace_ctype& operator=( const replace_ctype& ) = delete ;

        std::istream& stm ;
        const std::locale old_locale ;
    };

    replace_ctype temp(stm) ;

    return do_make_word_count(stm) ;
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
    // zebra Zebra zebra+giraffe Giraffe+ZEBRA zebra! zebra-foal zebra-crossing zebra.cadabra
    std::ifstream file( __FILE__ ) ;
    // ZEBRA ZEBRA ZEBRA+GIRAFFE GIRAFFE+ZEBRA ZEBRA! ZEBRA-FOAL ZEBRA-CROSSING ZEBRA.CADABRA

    const auto word_count = make_word_count(file) ;

    std::cout << "12 most used words\n--------------\n" ;
    copy_most_used( word_count, std::ostream_iterator<std::string>( std::cout, "\n" ), 12 ) ;
}
