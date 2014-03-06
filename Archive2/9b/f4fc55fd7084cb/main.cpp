#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

std::string new_account_number()
{
    static int n = 112280 ;
    ++n ;

    std::ostringstream stm ;
    stm << std::setw(8) << std::setfill('0') << n ;
    return stm.str() ;
}

int main()
{
    for( int i = 0 ; i < 5 ; ++i )
        std::cout << new_account_number() << '\n' ;
}
