#include <iostream>
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
    constexpr std::size_t TESTSZ = 1000 * 1000 * 2 ;
    
    std::set<std::string> set ;
    std::srand( std::time(0) ) ;

    std::string str ;
    auto begin_insert = std::clock() ;
    while( set.size() < TESTSZ )
    {
        str.resize( std::rand() % (MAXSZ-MINSZ+1) + MINSZ ) ;
        for( char& c : str ) c = alphabet[ std::rand() % N ] ;
        set.insert( std::move(str) ) ;
    }

    long long sum = 0 ;

    auto end_insert = std::clock() ;
    for( const std::string& s : set ) sum += s.size() ;
    auto end_iteration = std::clock() ;

    std::cout << "set size: " << set.size() << '\n' 
              << "processor time taken (insert): " << double( end_insert - begin_insert ) / CLOCKS_PER_SEC << " seconds\n"
              << "processor time taken (iterate): " << double( end_iteration - end_insert ) / CLOCKS_PER_SEC << " seconds\n"
              << "actual sum of sizes: " << sum << '\n'
              << "mathematical expectation: " << ( (MAXSZ+MINSZ) / 2LL ) * set.size() << '\n' ;
}
