#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

std::string new_account_number1()
{
    static int n = 112280 ;
    ++n ;

    std::ostringstream stm ;
    stm << std::setw(8) << std::setfill('0') << n ;
    return stm.str() ;
}

/*
std::string new_account_number2()
{
    static int n = 112280 ;
    ++n ;

    std::string str = "00000000" + std::to_string(n) ;
    return str.substr( str.size() - 8 ) ;
}
*/

int main()
{
    for( int i = 0 ; i < 5 ; ++i )
        std::cout << new_account_number1() /* << ' ' << new_account_number2() */ << '\n' ;
}
