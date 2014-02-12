#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

int main()
{
    constexpr char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "1234567890!@#$%^&*()_+`~[]{};':/?,.<>" ;
    constexpr std::size_t N = sizeof(alphabet) - 1 ;

    constexpr std::size_t MINSZ = 4 ;
    constexpr std::size_t MAXSZ = 20 ;
    constexpr std::size_t TESTSZ = 1000* 1000 * 32 ;

    std::vector<std::string> seq ;
    std::srand( std::time(0) ) ;

    while( seq.size() < TESTSZ )
    {
        std::string str( std::rand() % (MAXSZ-MINSZ+1) + MINSZ, 0 ) ;
        for( char& c : str ) c = alphabet[ std::rand() % N ] ;
        seq.push_back(str) ;
    }

    long long sum = 0 ;
    auto begin = std::clock() ;

    for( const std::string& s : seq ) sum += s.size() ;

    auto end = std::clock() ;

    std::cout << "elapse time: " << double( end - begin ) / CLOCKS_PER_SEC << " seconds.\n"
               << "actual sum: " << sum << '\n'
               << "mathematical expectation: " << ( (MAXSZ+MINSZ) / 2LL ) * seq.size() << '\n' ;

}
