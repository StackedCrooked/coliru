#include <iostream>
#include <string>
#include <sstream>

void split( const std::string& date, std::string& month, std::string& day, std::string& year )
{
    std::istringstream stm(date) ;
    if( std::getline( stm, month, '/' ) && std::getline( stm, day, '/' ) && std::getline( stm, year ) ) ; // ok
    else ; // parse error
}

int main()
{
    for( const std::string& date : { "05/10/1984", "4/15/84", "September/5/2014" } )
    {
        std::string month, day, year ;
        split( date, month, day, year ) ;
        std::cout << date << ' ' << month << ' ' << day << ' ' << year << '\n' ;
    }
}
