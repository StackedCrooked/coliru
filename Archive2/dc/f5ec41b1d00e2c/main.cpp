#include <iostream>
#include <iomanip>
#include <cctype>

int main()
{
    unsigned int acct ;
    
    // std::cout << "accout number (exactly six digits): " ;
    
    if( std::cin >> acct )
    {
        if( acct < 100000 )
            std::cout << "*** error: less than six digits were entered\n" ;
    
        else if( acct > 999999 ) 
        {
            while( acct > 999999 ) acct /= 10 ;
            std::cout << "* alert: more than 6 digits were entered. trailing digits are discarded."
                      << " account number: " << acct << '\n' ;
        }
        
        else std::cout << "well done! you entered exactly six digits. account number: " << acct << '\n' ;
    }
    
    else std::cout << "*** error: input is not numeric\n" ;
    
    std::cin.ignore( 10000, '\n' ) ; // throw away everything left in that line
}
