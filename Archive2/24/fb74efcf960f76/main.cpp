#include <ctime>
#include <memory>
#include <iostream>

const char* week_day_01_jan( int year )
{
    static const char* const wday[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" } ;

    auto now = std::time(nullptr) ;
    std::tm tm = *std::localtime( std::addressof(now) ) ;

    tm.tm_year = year - 1900 ;
    tm.tm_mday = 1 ;
    tm.tm_mon = 0 ; // january
    tm.tm_hour = 12 ; // noon
    const auto time = std::mktime( std::addressof(tm) ) ;

    return time == -1 ? "unknown" : wday[tm.tm_wday] ;
}

int main()
{
    for( int year : { 1950, 1980, 2014, 2015, 2022 } )
        std::cout << week_day_01_jan(year) << ", 01 Jan " << year << '\n' ;
}
