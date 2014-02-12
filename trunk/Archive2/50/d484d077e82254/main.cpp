#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

void print_results( std::size_t nfound, std::clock_t begin_insert, std::clock_t end_insert, std::clock_t end_find )
{
    constexpr double clocks_per_sec = CLOCKS_PER_SEC ;
    std::cout << "     #found: " << nfound << " strings\n"
              << "time insert: " << ( end_insert - begin_insert ) / clocks_per_sec << " secs\n"
              << "  time find: " << ( end_find - end_insert ) / clocks_per_sec << " secs\n"
              << " time total: " << ( end_find - begin_insert ) / clocks_per_sec << " secs\n\n\n" ;
}

int main()
{
    constexpr char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "1234567890!@#$%^&*()_+`~[]{};':/?,.<>" ;
    constexpr std::size_t N = sizeof(alphabet) - 1 ;

    constexpr std::size_t MINSZ = 4 ;
    constexpr std::size_t MAXSZ = 20 ;
    constexpr std::size_t TESTSZ = 1000 * 200 ;

    std::srand( std::time(0) ) ;
    std::cout << std::fixed ;
    std::cout.precision(3) ;

    // prepare test data set of 200,000 strings (average size: 12 characters)
    std::vector<std::string> test_data_set ;
    test_data_set.reserve(TESTSZ) ;
    std::string str ;
    while( test_data_set.size() < TESTSZ )
    {
        str.resize( std::rand() % (MAXSZ-MINSZ+1) + MINSZ ) ;
        for( char& c : str ) c = alphabet[ std::rand() % N ] ;
        test_data_set.push_back( std::move(str) ) ;
    }

    // insert into vector, and then find every string
    {
        std::vector<std::string> vector ;
        vector.reserve( test_data_set.size() ) ;

        auto begin_insert = clock() ;
        for( const std::string& s : test_data_set ) vector.push_back(s) ;
        std::sort( vector.begin(), vector.end() ) ;
        auto end_insert = std::clock() ;

        std::size_t nfound = 0 ;
        for( const std::string& s : test_data_set )
        {
            auto iter = std::lower_bound( vector.begin(), vector.end(), s ) ;
            if( iter != vector.end() ) ++nfound ;
        }
        auto end_find = std::clock() ;

        std::cout << "vector\n-----------------------------------------------\n" ;
        print_results( nfound, begin_insert, end_insert, end_find ) ; 
    }

    // insert into set, and then find every string
    {
        std::set<std::string> set ;

        auto begin_insert = clock() ;
        for( const std::string& s : test_data_set ) set.insert(s) ;
        auto end_insert = std::clock() ;

        std::size_t nfound = 0 ;
        for( const std::string& s : test_data_set )
        {
            auto iter = set.find(s) ;
            if( iter != set.end() ) ++nfound ;
        }
        auto end_find = std::clock() ;

        std::cout << "set\n-----------------------------------------------\n" ;
        print_results( nfound, begin_insert, end_insert, end_find ) ; 
    }

    // insert into unordered set, and then find every string
    {
        std::unordered_set<std::string> set ;

        auto begin_insert = clock() ;
        for( const std::string& s : test_data_set ) set.insert(s) ;
        auto end_insert = std::clock() ;

        std::size_t nfound = 0 ;
        for( const std::string& s : test_data_set )
        {
            auto iter = set.find(s) ;
            if( iter != set.end() ) ++nfound ;
        }
        auto end_find = std::clock() ;

        std::cout << "unordered_set\n-----------------------------------------------\n" ;
        print_results( nfound, begin_insert, end_insert, end_find ) ; 
    }
}
