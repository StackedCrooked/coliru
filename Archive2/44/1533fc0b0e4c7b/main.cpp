#include <iostream>
#include <map>
#include <vector>

typedef std::vector<std::string> mapped_type ;
typedef std::map< std::string, mapped_type > dictionary_type ;

mapped_type look_up( const dictionary_type& dict, const std::string& word )
{
    dictionary_type::const_iterator iter = dict.find(word) ;
    if( iter != dict.end() ) return iter->second ;
    else return mapped_type() ;
}

int main()
{
    dictionary_type dict ;

    // insert
    dict[ "Cat" ].push_back( "Siamese") ;
    dict[ "Cat" ].push_back( "Persian") ;
    dict[ "Cat" ].push_back( "Bengal") ;
    dict[ "Cat" ].push_back( "Devon") ;
    dict[ "Cat" ].push_back( "Angora") ;

    dict[ "Dog" ].push_back( "Beagle") ;
    dict[ "Dog" ].push_back( "Pug") ;
    dict[ "Dog" ].push_back( "Dalmatian") ;

    // look_up
    std::cout << "Cat\n" ;
    mapped_type vec = look_up( dict, "Cat" ) ;
    for( std::size_t i = 0 ; i < vec.size() ; ++i )
        std::cout << "  " << vec[i] << '\n' ;
    std::cout << '\n' ;

    std::cout << "Dog\n" ;
    vec = look_up( dict, "Dog" ) ;
    for( std::size_t i = 0 ; i < vec.size() ; ++i )
        std::cout << "  " << vec[i] << '\n' ;
    std::cout << '\n' ;

    std::cout << "Rabbit\n" ;
    vec = look_up( dict, "Rabbit" ) ;
    for( std::size_t i = 0 ; i < vec.size() ; ++i )
        std::cout << "  " << vec[i] << '\n' ;
    std::cout << '\n' ;

}
