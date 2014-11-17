#include <iostream>
#include <algorithm>
#include <string>
#include <utility>

bool quotient_is_9( std::pair<int,int> numbers ) { return numbers.first == ( numbers.second * 9 ) ; }

// invariant: str contains decimal digits, str.size() == 9
std::pair<int,int> split54( std::string str ) 
{ return { std::stoi( str.substr(0,5) ), std::stoi( str.substr(5) ) }; }

int main()
{
    std::string digits = "123456789" ;
    int cnt = 0 ;
    
    do if( quotient_is_9( split54(digits) ) ) ++cnt ; 
    while( std::next_permutation( std::begin(digits), std::end(digits) ) ) ;

    std::cout << cnt << '\n' ;
}
