#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <typeindex>
#include <stdexcept>
#include <sstream>

struct config
{
    enum { NO_ID = 999 };

    std::string getFromDB( int /* id */ ) const { throw std::domain_error( "no id" ) ; }

    template < typename T > void add_item( std::string name, T& value, int id = NO_ID )
    {
        const std::string str_value = stringify(value) ;
        if( id != NO_ID ) { /* try write/update DB with name/str_value*/ }
        std::type_index ti = typeid(value) ;
        name_value_map.emplace( name, std::make_pair( ti, str_value ) ) ;
    }

    template < typename T > T& get( std::string name, T& value, int id = NO_ID ) const
    {
        std::string str_value = look_up( name, typeid(value) ) ;

        if( id != NO_ID )
        {
            try { str_value = getFromDB(id) ; }
            catch( const std::exception& ) {}
        }

        std::istringstream stm(str_value) ;
        stm >> std::boolalpha >> value ;
        return value ;
    }

    private:
        std::map< std::string, std::pair< std::type_index, std::string > > name_value_map
        {
            { "a1", { typeid(bool), "true" } },
            { "a2", { typeid(bool), "false" } },
            { "a3", { typeid(bool), "true" } },
            { "size",  { typeid(std::size_t), std::to_string(999) } },
            { "when",  { typeid(std::time_t), std::to_string( std::time(nullptr) ) } },
            { "greeting",  { typeid(std::string), "hello" } }
        };

        template < typename T > std::string stringify( const T& v )
        {
            std::ostringstream stm ;
            stm << std::boolalpha << v ;
            return stm.str() ;
        }

        std::string look_up( std::string name, std::type_index ti ) const
        {
            const auto iter = name_value_map.find(name) ;

            if( iter == name_value_map.end() ) throw std::domain_error( "no name" ) ;
            else if( ti != iter->second.first ) throw std::domain_error( "bad type" ) ;

            return iter->second.second ;
        }
};

int main()
{
    config cfg ;

    bool b1, b2 ;
    std::size_t s ;
    std::time_t t ;
    std::string str ;
    std::cout << std::boolalpha << "a1: " << cfg.get( "a1", b1 ) << '\n'
              << "a2: " << cfg.get( "a2", b2 ) << '\n'
              << "size: " << cfg.get( "size", s ) << '\n'
              << "when: " << cfg.get( "when", t ) << '\n'
              << "greeting: " << cfg.get( "greeting", str ) << '\n' ;

    try { std::cout << "colour: " << cfg.get( "colour", b1 ) << '\n' ; }
    catch( const std::exception& e ) { std::cerr << "error: " << e.what() << '\n' ; }

    try { std::cout << "size: " << cfg.get( "size", b1 ) << '\n' ; }
    catch( const std::exception& e ) { std::cerr << "error: " << e.what() << '\n' ; }

    long clr = 778899 ;
    cfg.add_item( "colour", clr ) ;

    clr = 0 ;
    std::cout << "colour: " << cfg.get( "colour", clr ) << '\n' ;
}
