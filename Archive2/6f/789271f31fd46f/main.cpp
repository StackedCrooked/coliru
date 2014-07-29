#include <iostream>
#include <ctime>

int main()
{
    // http://en.cppreference.com/w/cpp/chrono/c/time
    std::time_t now = std::time( 0 ) ; // current time (since epoch)
    
    // convert to calendar time 
    // http://en.cppreference.com/w/cpp/chrono/c/localtime
    std::tm* ptm = std::localtime( &now ) ; 
    char cstr[ 128 ] ;

    // format and print
    // http://en.cppreference.com/w/cpp/chrono/c/strftime
    std::strftime( cstr, sizeof( cstr ), "%c", ptm ) ;
    std::cout << "local time now: " << cstr << '\n' ;

    ptm->tm_hour += 100 ; // add 100 hours 

    // ptm->tm_hour would now be out of range; normalise 
    // http://en.cppreference.com/w/cpp/chrono/c/mktime
    std::time_t now_plus_100_hrs = std::mktime( ptm ) ;
    ptm = std::localtime( &now_plus_100_hrs ) ;

    // format and print
    std::strftime( cstr, sizeof( cstr ), "%c", ptm ) ;
    std::cout << "local time 100 hours from now: " << cstr << '\n' ;
}
