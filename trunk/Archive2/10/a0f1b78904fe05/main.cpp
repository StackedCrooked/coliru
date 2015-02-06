#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <map>
#include <functional>
#include <algorithm>

struct object
{
    const std::string id ;

    static const object& cget( const std::string& id ) { return get(id) ; }
    static object& get( const std::string& id )
    {
        const auto iter = id_map.find(id) ;
        if( iter == id_map.end() ) throw std::out_of_range( "id '" + id + "' not found" ) ;
        return *iter->second ;
    }

    object( int v = 0 ) : id( random_unique_id() ), value(v) { id_map.emplace( id, this ) ; }
    object( const object& that ) : object( that.value ) {} // ids are not copied
    object( object&& that ) noexcept : object( that.value ) {}
    object& operator= ( const object& that ) { value = that.value ; return *this ; }
    object& operator= ( object&& that ) noexcept { value = that.value ; return *this ; }
    ~object() { id_map.erase(id) ; }

    static std::map< std::string, object* const > id_map ;
    static const std::size_t ID_SIZE = 8 ;
    static std::string random_unique_id() ;

    int value ;
};

std::map< std::string, object* const > object::id_map ;

std::string object::random_unique_id()
{
    static std::mt19937 rng( std::time(nullptr) ) ;
    static std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" ;

    std::shuffle( std::begin(alphabet), std::end(alphabet), rng ) ;
    std::string candidate = alphabet.substr( 0, ID_SIZE ) ;
    return id_map.find(candidate) == id_map.end() ? candidate : random_unique_id() ;
}

int main()
{
    object seq[4] ;
    for( const object& obj : seq ) std::cout << obj.id << ' ' << std::addressof(obj) << '\n' ;

    object x = seq[2] ;
    const std::string id_x = x.id ;
    std::cout << id_x << ' ' << object::get(id_x).id << ' '
              << std::addressof(x) << ' ' << std::addressof( object::get(id_x) ) << '\n'
              << seq[2].id << ' ' << seq+2 << ' ' << std::addressof( object::cget( seq[2].id ) ) << '\n';
}
