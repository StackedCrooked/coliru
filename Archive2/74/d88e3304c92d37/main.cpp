#include <iostream>
#include <string>

void split( const std::string& date, std::string& month, std::string& day, std::string& year )
{
    std::size_t pos = date.find('/') ;
    if( pos != std::string::npos )
    {
        month = date.substr( 0, pos ) ;
        ++pos ; // get to character after the '/'

        std::size_t pos2 = date.find( '/', pos ) ;
        if( pos != std::string::npos )
        {
            day = date.substr( pos, pos2-pos ) ;
            year = date.substr(pos2+1) ;
            return ; // fine, we are done
        }
    }

    month = day = year = "" ; // parse error
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
