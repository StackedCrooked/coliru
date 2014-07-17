#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <fstream>
#include <strstream> // deprecated
#include <cctype>
#include <locale>
#include <string>
#include <ctime>

int main()
{
    const char* const path = "/tmp/test.txt" ;
    
    {
        // create a big file with lots of punctuation (html)
        std::ofstream file(path) ;
        for( int i = 0 ; i < 25 ; ++i ) file << std::ifstream( "/usr/share/doc/bc/bc.html" ).rdbuf() ;
    }
    
    using namespace boost::interprocess ;
    file_mapping mapping( path, read_only ) ;
    mapped_region region( mapping, read_only) ;
    const std::size_t nbytes  = region.get_size() ;
    const char* const address = static_cast<  const char* >( region.get_address() ) ;
    
    std::istrstream stm( address, nbytes ) ; // deprecated
    
    // This ctype facet classifies all punctuations too as whitespace
    struct punct_too_is_ws : std::ctype<char>
    {
        static const mask* classification_table()
        {
            // start with the classic table ( C locale's table )
            static std::vector<mask> table( classic_table(),  classic_table() + table_size ) ;

            // all punctuation is to be treated as whitespace
            for( std::size_t i = 0 ; i < table_size ; ++i ) if( std::ispunct(i) ) table[i] = space ;

            return std::addressof( table.front() ) ;
        }

        // do not delete table, initial reference count == 0
        punct_too_is_ws() : std::ctype<char>( classification_table() ) {}
    };
    
    stm.imbue( std::locale( stm.getloc(), new punct_too_is_ws ) ) ;
    
    std::string str ;
    std::size_t cnt = 0 ;
    
    const auto start = std::clock() ;
    while( stm >> str ) ++cnt ;
    const auto end = std::clock() ;
    
    std::cout << cnt << " words were read in " << double(end-start)*1000 / CLOCKS_PER_SEC << " milliseconds.\n" ;
}