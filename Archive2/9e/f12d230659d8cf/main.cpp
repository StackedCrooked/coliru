#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>

struct object
{
    std::string id ;
    object( std::string&& name = "" ) : id( std::move(name) ) {}
};

object random_object()
{
    static char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
    static constexpr std::size_t N = sizeof(alphabet) - 1 ;
    static std::mt19937 twister( std::time(nullptr) ) ;
    static std::uniform_int_distribution<std::size_t> distr( 2, 10 ) ;

    std::shuffle( alphabet, alphabet+N, twister ) ;
    return { { alphabet, alphabet + distr(twister) } } ;
}

int main()
{
    const std::size_t N = 1024 * 128 ;

    std::vector<object> master ;
    while( master.size() < N ) master.push_back( random_object() ) ;
    std::cout << "master size: " << master.size() << '\n' ;

    constexpr int REPEAT = 5 ;
    std::srand( std::time(nullptr) ) ;
    std::vector< object > subset ;
    for( int i = 0 ; i < REPEAT ; ++i )
    {
        // create random subset
        subset.clear() ;
        for( std::size_t j = i ; j < N ; j +=  2 + i*2 ) subset.push_back( master[j] ) ;
        std::random_shuffle( subset.begin(), subset.end() ) ; // rearrange subset

        const auto start = std::clock() ;

        // destructively move subset elements to a hash table
        std::unordered_set<std::string> set ;
        for( object& obj : subset ) set.insert( std::move( obj.id ) ) ;

        std::vector< object > temp ; // scratch area

        // iterate through the master, look up, append to temp
        for( const object& obj : master )
        {
            auto iter = set.find(obj.id) ;
            if( iter != set.end() )
            {
                std::string mvalue = *iter ;
                temp.emplace_back( std::move(mvalue) ) ;
            }
        }

        subset.swap(temp) ; // copy temp to subset, discard subset

        const auto end = std::clock() ;
        std::cout << "subset size: " << subset.size() << ' ' << ( end - start ) / double(CLOCKS_PER_SEC) << " seconds.\n" ;
    }
}
