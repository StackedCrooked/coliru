#include <vector>
#include <iterator>
#include <algorithm>

template < typename ITERATOR, typename ITERATOR2 >
bool less_or_equal( ITERATOR begin, ITERATOR end, ITERATOR2 begin2 )
{
    for ( ; begin != end ; ++begin, ++begin2 )
    {
        if( *begin < *begin2 ) return true ;
        if( *begin > *begin2 ) return false ;
    }
    return true ;
}

std::vector<int>& next_palindrome( std::vector<int>& number )
{
    if( number.empty() || number.front() == 0 ) return number = {1} ;

    auto begin = number.begin() ;
    auto end = number.begin() + number.size() / 2 + number.size()%2 ;
    std::reverse_iterator<decltype(end)> rbegin(end) ;
    std::reverse_iterator<decltype(end)> rend(begin) ;

    if( less_or_equal( rbegin, rend, begin+number.size()/2 ) )
    {
        auto iter = rbegin ;
        while( *iter == 9 && iter != rend ) { *iter = 0 ; ++iter ; }
        if( iter != rend ) ++ *iter ;
        else
        {
            std::fill( begin+number.size()/2, number.end(), 0 ) ;
            number.push_back(1) ;
            number.front() = 1 ;
            return number ;
        }
    }

    std::copy( begin, end, number.rbegin() ) ;
    return number ;
}

#include <iostream>
#include <ctime>
#include <sstream>
#include <cstdlib>

int main()
{
    static constexpr std::size_t MILLION = 1000 * 1000 ;

    ////////////// for the actual submission, comment out this part ////////////
    // it sets up std::cin to read our test data

    std::string test_data =
        "10\n" // number of test cases on first line
        "808\n" // followed by one test case per line
        "2133\n"
        "99999999999999999999999999999999999999999999999999999999999\n"
        "123456789012345678901234567890123456789012345678900\n"
        "1111111112222222222222333333333444444444445555555555555556666666666\n"
        "11111111111111111111111111111111990011111111111111111111111111111111\n"
        "111111111111111111111111111111119999971111111111111111111111111111111\n"
        "11111111111111111111111111111111989911111111111111111111111111111111\n"
        "123456789009876543211234567890098765432112345678900987654321\n" ;

     // the last test case is for a number with a million digits
     // and we make it a worst-case performance test case
     test_data += '1' ;
     test_data.insert( test_data.end(), MILLION-2, '9' ) ;
     test_data += "2\n" ;

     std::istringstream input(test_data) ;
     std::cin.rdbuf( input.rdbuf() ) ;

     /////////////  comment out the above part /////////////////////////////////

     auto begin = std::clock() ;

     int n_testcases ;
     input >> n_testcases ;
     input.ignore( 1024, '\n' ) ; // throw away a newline

     std::vector<int> number ;
     number.reserve(MILLION) ;

     for( int i = 0 ; i < n_testcases ; ++i )
     {
        std::string line ;
        std::getline( input, line ) ;
        std::istringstream stm(line) ;

        std::istreambuf_iterator<char> begin(stm), end ;
        number.resize(0) ;
        for( ; begin != end ; ++begin ) number.push_back( *begin - '0' ) ;

        const auto print_big_number = [&number]
        {
            std::cout << "number with " << number.size() << " digits: " ;
            for( int i = 0 ; i < 4 ; ++i ) std::cout << number[i] ;
            std::cout << " ... " ;
            for( int i = 4 ; i > 0 ; --i ) std::cout << number[ number.size()-i ] ;
        };

        if( number.size() < 1000 ) for( int v : number ) std::cout << v ;
        else print_big_number() ;
        std::cout << '\n' ;

        next_palindrome(number) ;

        if( number.size() < 1000 ) for( int v : number ) std::cout << v ;
        else print_big_number() ;
        std::cout << "\n\n" ;
     }

     auto end = std::clock() ;
     std::cout << double(end-begin) / CLOCKS_PER_SEC << " seconds" << std::endl ;

     return std::system( "uname -a" /*"&& cat /proc/cpuinfo | grep MHz"*/ ) ;
}
