#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

void background_thread_function() 
{
    for( int i=0 ; i<5 ; ++i )
    {
        std::cout << "background_thread does some work\n" << std::flush ;
        std::this_thread::sleep_for( std::chrono::seconds(2) ) ; // sleeps for two seconds
    }
}

int main()
{
    std::cout << "creating background thread\n" << std::flush ;
    std::thread bkthread( background_thread_function ) ;
    
    for( int i = 0 ; i < 2000 ; ++i )
    {
        std::cout << '.' << std::flush ;
        if( i%200 == 199 ) 
        {
            std::cout << '\n' << std::flush ;
            std::this_thread::sleep_for( std::chrono::seconds(1) ) ; // sleeps for one seconds
        }
    }
    
    bkthread.join() ;
}
