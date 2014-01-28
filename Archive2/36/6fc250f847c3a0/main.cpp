#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

void sleep( unsigned int secs )
{ std::this_thread::sleep_for( std::chrono::seconds(secs) ) ; }

void sleep( unsigned int hrs, int mins, int secs )
{ sleep( hrs*3600 + mins*60 + secs ) ; }

void usleep( unsigned int usec )
{ std::this_thread::sleep_for( std::chrono::microseconds(usec) ) ; }

void nanosleep( unsigned int secs, unsigned int nanosecs )
{
    std::this_thread::sleep_for( std::chrono::seconds(secs) +
                                 std::chrono::nanoseconds(nanosecs) ) ;
}

void wall_clock()
{
    auto t = std::time(nullptr) ;
    char cstr[128] ;
    std::strftime( cstr, sizeof(cstr), "%H:%M:%S UTC", std::gmtime(&t) ) ;
    std::cout << cstr << '\n' << std::flush ;
}

int main()
{
    wall_clock() ;

    sleep(2) ;
    wall_clock() ;

    usleep(3000000) ;
    wall_clock() ;

    nanosleep( 3, 999999999 ) ;
    wall_clock() ;
}
