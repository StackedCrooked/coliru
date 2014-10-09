#include <iostream>
#include <fstream>
#include <string>
#include<map>
#include <vector>
#include <future>

// first == path to file second == count of occurrences of unique tokens
using result_type = std::pair< std::string, std::map< std::string, std::size_t > > ;

// get token-count of one file
result_type token_count( const std::string& path )
{
    result_type result { path, {} } ;
    std::ifstream file( path ) ;
    std::string token ;
    while( file >> token ) ++result.second[token] ;
    return result ;
}

// print first n tokens from one file
void print( const result_type& result, std::size_t n = 10 )
{
    std::cout << "file: " << result.first << '\n' ;
    std::size_t cnt = 0 ;
    for( const auto& pair : result.second )
    {
        if( cnt == n ) break ;
        std::cout << '\t' << ++cnt << ". " << pair.first << " - " << pair.second << '\n' ;
    }
}

int main()
{
    std::vector< std::string > paths_to_files { "a.txt", "b.txt", "c.txt" } ;
    std::ofstream( paths_to_files[0] ) << "one two three four five six seven one two three four five one two three\n" ; 
    std::ofstream( paths_to_files[1] ) << "to be or not to be that is the question be Whether 'tis it is nobler in the mind to be\n" ; 
    std::ofstream( paths_to_files[2] ) << "Happy families are all alike are all alike all alike alike every unhappy family is unhappy in its own way\n" ; 

    // http://en.cppreference.com/w/cpp/thread/future
    std::vector< std::future<result_type> > results ;
    // http://en.cppreference.com/w/cpp/thread/async.html
    for( const std::string& path : paths_to_files )
        results.push_back( std::async( std::launch::async, token_count, path ) ) ;

    for( auto& future : results )
    {
        // http://en.cppreference.com/w/cpp/thread/future/get.html
        const auto& result = future.get() ;
        print( result ) ;
    }
}
