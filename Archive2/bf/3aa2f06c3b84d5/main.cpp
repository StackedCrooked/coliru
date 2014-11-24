#include <iostream>
#include <future>
#include <chrono>
#include <atomic>

namespace
{
    std::atomic<bool> timeout ; // http://en.cppreference.com/w/cpp/atomic/atomic
    
    const int ERROR = -1 ; // error returned on timeout or eof
    
    const int MSECS_INTERVAL = 500 ; 
    const int MSECS_TIMEOUT = 10000 ;
}

int get_choice( int minv, int maxv )
{
    int v ;
    std::cout << "choose an option " << minv << '-' << maxv << ": " ;
    if( std::cin >> v && v >= minv && v <= maxv ) return v ;
    
    if( std::cin.eof() ) return ERROR ; 
    
    // http://en.cppreference.com/w/cpp/io/basic_ios/clear
    std::cin.clear() ; // clear failed state
    
    // http://en.cppreference.com/w/cpp/io/basic_istream/ignore
    std::cin.ignore( 1000, '\n' ) ; // throw away incorrect input
    
    std::cout << "invalid input. please try again\n" ;
    return timeout ? ERROR : get_choice( minv, maxv ) ; // try again if not timed out
}

int main()
{
    timeout = false ;
    // http://en.cppreference.com/w/cpp/thread/async
    auto future = std::async( std::launch::async, get_choice, 1, 7 ) ;
    
    int millisecs = 0 ;
    while( millisecs < MSECS_TIMEOUT )
    {
           // http://en.cppreference.com/w/cpp/thread/future/wait_for     
           if( future.wait_for( std::chrono::milliseconds(MSECS_INTERVAL) ) == std::future_status::ready ) 
           {
               timeout = false ;
               break ;
           }
           else millisecs += MSECS_INTERVAL ; 
    }
    
    int choice = ERROR ;
    if( !timeout ) choice = future.get() ; 
    
    if( choice == ERROR ) 
    {
        std::cout << "input timed out. you can't read this because you are dead\n" ;
        // ...
    }
    
    else
    {
        std::cout << "your choice is: " << choice << '\n' ;
        // ...
    }
}
