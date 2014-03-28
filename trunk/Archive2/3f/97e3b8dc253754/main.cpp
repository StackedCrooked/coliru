#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
    // long unsigned int num;
    unsigned long long num;
    // int i;

    std::cout << "ENTER A 9 DIGIT NUMBER : " ;  //ask user to enter integer
    std::cin >> num;

    std::cout << "\nnumber: " << num << '\n' ;
        
    std::ostringstream out ;
    out << num ;
    std::string result = out.str() ;
    std::reverse( result.begin(), result.end() ) ;

    for( int i = 0 ; i < 10 ; ++i )
    {
        const char digit = i + '0' ;

        if( std::count( result.begin(), result.end(), digit ) > 0 )
        {
            std::cout << i << ": " ;

            for( std::size_t pos = 0 ; pos < result.size() ; ++pos )
                if( result[pos] == digit  ) std::cout << pos << ' ' ;

            std::cout << '\n' ;
        }
    }
}
