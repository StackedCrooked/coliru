#include <iostream>
#include <unordered_map>
#include <cstring>

struct Infoclass{ int v ; operator int() const { return v ; } } ;

struct InfoHashTable
{
    struct hash
    {
        std::size_t operator() ( const char* key ) const // djb2 (dan bernstein)
        {
            std::size_t h = 5381;
            while( std::size_t c = *reinterpret_cast<const unsigned char*>(key++) ) h = h*33 + c ;
            return h ;
        }
    };

    struct equal_to
    {
        bool operator() ( const char* a, const char* b ) const { return !std::strcmp(a,b) ; }
    };

    std::unordered_map< const char*, Infoclass*, hash, equal_to > hashtable ;

    bool insert( const char* key, Infoclass* value ) { return hashtable.emplace(key,value).second ; }
    Infoclass* find( const char* key )
    {
        const auto iter = hashtable.find(key) ;
        return iter != hashtable.end() ? iter->second : nullptr ;
    }
};

int main()
{
    char keys[][12] = { "one", "two", "three", "four", "five", "six" } ;
    constexpr std::size_t N = sizeof(keys) / sizeof(keys[0]) ;

    Infoclass objects[N] = { {1}, {2}, {3}, {4}, {5}, {6} } ;

    InfoHashTable iht ;
    for( std::size_t i = 0 ; i < N ; ++i ) iht.insert( keys[i], objects+i ) ;

    for( const char* k : { "two", "five", "twelve", "three", "eight" } )
    {
        std::cout << '\'' << k << '\'' ;
        const auto p = iht.find(k) ;
        if(p) std::cout << " => " << *p << '\n' ;
        else  std::cout << " was not found\n" ;
    }
}
