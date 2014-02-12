#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

int main()
{
    constexpr char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "1234567890!@#$%^&*()_+`~[]{};':/?,.<>" ;
    constexpr std::size_t N = sizeof(alphabet) - 1 ;

    constexpr std::size_t MINSZ = 4 ;
    constexpr std::size_t MAXSZ = 20 ;
    constexpr std::size_t TESTSZ = 1000 * 200 ;

    std::srand( std::time(0) ) ;
    constexpr double clocks_per_sec = CLOCKS_PER_SEC ;
    
    // prepare test data set of 200000 strings
    std::vector<std::string> test_case ;
    test_case.reserve(TESTSZ) ;
    std::string str ;
    while( test_case.size() < TESTSZ )
    {
        str.resize( std::rand() % (MAXSZ-MINSZ+1) + MINSZ ) ;
        for( char& c : str ) c = alphabet[ std::rand() % N ] ;
        test_case.push_back( std::move(str) ) ;
    }
    
    // insert into vector, find every string
    {
        std::vector<std::string> vector ;
        vector.reserve( test_case.size() ) ;
        
        auto begin_insert = clock() ;
        for( const std::string& s : test_case ) vector.push_back(s) ;
        std::sort( vector.begin(), vector.end() ) ;
        auto end_insert = std::clock() ;
        
        std::size_t nfound = 0 ;
        for( const std::string& s : test_case ) 
        {
            auto iter = std::lower_bound( vector.begin(), vector.end(), s ) ;
            if( iter != vector.end() ) ++nfound ;
        }
        auto end_find = std::clock() ;
        
        std::cout << "vector\n------\n" 
                  << "                  nfound: " << nfound << '\n'
                  << "time taken (insert,sort): " << ( end_insert - begin_insert ) / clocks_per_sec << " secs\n" 
                  << "       time taken (find): " << ( end_find - end_insert ) / clocks_per_sec << " secs\n" 
                  << "        total time taken: " << ( end_find - begin_insert ) / clocks_per_sec << " secs\n\n" ;
                  
    }
    
    // insert into set, find every string
    {
        std::set<std::string> set ;
        
        auto begin_insert = clock() ;
        for( const std::string& s : test_case ) set.insert(s) ;
        auto end_insert = std::clock() ;

        std::size_t nfound = 0 ;
        for( const std::string& s : test_case ) 
        {
            auto iter = set.find(s) ;
            if( iter != set.end() ) ++nfound ;
        }
        auto end_find = std::clock() ;
        
        std::cout << "set\n------\n" << "nfound: " << nfound << '\n'
                  << "      time taken (insert): " << ( end_insert - begin_insert ) / clocks_per_sec << " secs\n" 
                  << "        time taken (find): " << ( end_find - end_insert ) / clocks_per_sec << " secs\n"
                  << "         total time taken: " << ( end_find - begin_insert ) / clocks_per_sec << " secs\n\n" ;
    }
}
