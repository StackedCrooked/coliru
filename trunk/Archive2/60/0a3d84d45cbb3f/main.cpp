#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

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

void main_( std::size_t N )
{
    std::vector<object> master ;
    while( master.size() < N ) master.push_back( random_object() ) ;
    std::cout << "Master size: " << master.size() << "  " << std::fixed << std::setprecision(2);

    std::srand( std::time(nullptr) ) ;
    std::vector< object > _subset;  // create random subset
    for( std::size_t j = 0 ; j < N ; j += 2 ) _subset.push_back( master[j] ) ;
    std::random_shuffle( _subset.begin(), _subset.end() ) ; // rearrange subset
    std::vector< object > subset[3] = {_subset, _subset, _subset};  // all 3 tests should use the same subset

    {    // Test #1. Sort subset[0] according to order in master.
        const auto start = std::clock() ;
	    // destructively move subset elements to a hash table
        std::unordered_set<std::string> set ;
        for( object& obj : subset[0] ) set.insert( std::move( obj.id ) ) ;
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
        subset[0].swap(temp) ; // copy temp to subset, discard subset
        const auto end = std::clock() ;
        std::cout << "1. " << std::setw(6) << subset[0].size() << ' '  << ( end - start ) / double(CLOCKS_PER_SEC) << " secs.  " ;
    }
    {	// Test #2.  Sort subset[1] according to reverse order in master.
        const auto start = std::clock() ;
        std::unordered_set<std::string> set ;
        for( object& obj : subset[1] ) set.insert( std::move( obj.id ) ) ;
        std::vector< object > temp ;
        for(std::vector<object>::const_reverse_iterator it = master.crbegin(); it != master.crend(); ++it)
        {
            auto iter = set.find(it->id) ;
            if( iter != set.end() )
            {
                std::string mvalue = *iter ;
                temp.emplace_back( std::move(mvalue) ) ;
            }
        }
        subset[1].swap(temp) ;
        const auto end = std::clock() ;
        std::cout << "2. " << std::setw(6) << subset[1].size() << ' '  << ( end - start ) / double(CLOCKS_PER_SEC) << " secs.  " ;
    }
    {	// Test #3.  Sort subset[3] according to master[0] < master[N-1] < master[1] < master[N-2] < master[2] < master[N-3] < master[3] < ...
        const auto start = std::clock() ;
        std::unordered_set<std::string> set ;
        for( object& obj : subset[2] ) set.insert( std::move( obj.id ) ) ;
        std::vector< object > temp ;
        auto it = master.begin() ;
        auto jt = master.crbegin() ;
        while ( it < jt.base() )  
	    {
	        {
	            auto iter = set.find(it->id) ;
	            if( iter != set.end() )
	            {
	                std::string mvalue = *iter ;
	                temp.emplace_back( std::move(mvalue) ) ;
	            }
	            iter = set.find(jt->id) ;
	            if( iter != set.end() )
	            {
	                std::string mvalue = *iter ;
	                temp.emplace_back( std::move(mvalue) ) ;
	            }
	            ++it;  ++jt;
	        }
	    }
        subset[2].swap(temp) ;
        const auto end = std::clock() ;
        std::cout << "3. " << std::setw(6) << subset[2].size() << ' '  << ( end - start ) / double(CLOCKS_PER_SEC) << " secs.\n" ;
    }
}

int main()
{
    std::size_t N = 1024 * 64 ;
    for( int i = 0 ; i < 3 ; ++i ) main_( N *= 2 ) ;
}
