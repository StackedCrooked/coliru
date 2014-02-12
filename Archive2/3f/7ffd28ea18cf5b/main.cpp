#include <iostream>
#include <vector>
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
    constexpr std::size_t TESTSZ = 1000 * 1000 * 32 ;

    std::vector<std::string> seq ;
    seq.reserve(TESTSZ) ;
    std::srand( std::time(0) ) ;

    std::string str ;
    auto begin_insert = std::clock() ;
    while( seq.size() < TESTSZ )
    {
        str.resize( std::rand() % (MAXSZ-MINSZ+1) + MINSZ ) ;
        for( char& c : str ) c = alphabet[ std::rand() % N ] ;
        seq.push_back( std::move(str) ) ;
    }
    auto end_insert = std::clock() ;

    long long sum = 0 ;

    for( const std::string& s : seq ) sum += s.size() ;
    auto end_iteration = std::clock() ;
    std::sort( seq.begin(), seq.end(), []( const std::string& a, const std::string& b ) { return a.size() < b.size() ; } ) ;
    auto end_sort = std::clock() ;
    

    std::cout << "vector size: " << seq.size() << '\n' 
              << "processor time taken (insert): " << double( end_insert - begin_insert ) / CLOCKS_PER_SEC << " seconds\n"
              << "processor time taken (iterate): " << double( end_iteration - end_insert ) / CLOCKS_PER_SEC << " seconds\n"
              << "processor time taken (sort ascending on size): " << double( end_sort - end_iteration ) / CLOCKS_PER_SEC << " seconds\n"
              << "actual sum of sizes: " << sum << '\n'
              << "mathematical expectation: " << ( (MAXSZ+MINSZ) / 2LL ) * seq.size() << '\n' ;
}
