#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <future>

int foo( const char* name, int cnt )
{
    for( int i = 0 ; i < cnt ; ++i )
    {
        static std::atomic<int> n(0) ;
        std::cout << name << std::flush ;
        if( ++n%20 == 0 ) std::cout << std::endl ; 
        std::this_thread::sleep_for( std::chrono::milliseconds(10) ) ;
    }
    
    return cnt ;
}

int main()
{
    std::thread threads[] = { std::thread( foo, "one ", 10 ), std::thread( foo, "two ", 15 ), std::thread( foo, "three ", 20 ) } ;
    std::future<int> futures[] = { std::async( std::launch::async, foo, "four ", 25 ), std::async( std::launch::async, foo, "five ", 30 ) } ;
    
    for( std::thread& t : threads ) t.join() ;
    for( auto& f : futures ) f.wait() ;
}
