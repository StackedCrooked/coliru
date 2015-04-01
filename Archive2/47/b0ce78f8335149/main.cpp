#include <iostream>
#include <string>
#include <functional>
#include <unordered_set>
#include <type_traits>

struct my_string_hash
{
    static constexpr std::size_t MULTIPLIER = 37 ;

    std::size_t operator() ( const std::string & key ) const noexcept // *** const ***
    {
        std::size_t hash_value = 0 ;
        for( unsigned char ch : key )
            hash_value = hash_value * MULTIPLIER + ch ;
        return hash_value ;
    }
};

template < typename T >
using my_hash = typename std::conditional< std::is_same< typename std::decay<T>::type, std::string >::value,
                                           my_string_hash, std::hash<T> >::type ;

template < typename T >
using my_unordered_set = std::unordered_set< T, my_hash<T> > ;

int main()
{
    my_unordered_set<int> int_set ;
    static_assert( std::is_same< decltype(int_set)::hasher, std::hash<int> >::value, "unexpected hash function" ) ;
    
    my_unordered_set<std::string> str_set ;
    static_assert( std::is_same< decltype(str_set)::hasher, my_string_hash >::value, "unexpected hash function" ) ;
}
