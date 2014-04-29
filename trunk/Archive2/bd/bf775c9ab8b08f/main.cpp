#include <iostream>
#include <thread>
#include <string>
#include <atomic>
#include <chrono>
#include <future>

struct my_class
{
    int thread_fun( std::string name, int cnt ) const
    {
        name += suffix ;
        name += ' ' ;
        
        for( int i = 0 ; i < cnt ; ++i )
        {
            std::cout << name << std::flush ;
    
            static std::atomic<int> n(0) ;
            if( ++n%20 == 0 ) std::cout << std::endl ; 

            std::this_thread::sleep_for( std::chrono::milliseconds(5) ) ;
        }
        
        return cnt ;
    }
    
    char suffix ;
};

int main()
{
    my_class mc[5] { {'.'}, {'!'}, {'*'}, {'+'}, {'$'} } ;
    auto fn = &my_class::thread_fun ;
    std::thread threads[] = { std::thread( fn, mc, "one", 10 ), std::thread( fn, mc+1, "two", 15 ), std::thread( fn, mc+2, "three", 20 ) } ;
    std::future<int> futures[] = { std::async( std::launch::async, fn, mc+3, "four", 25 ), std::async( std::launch::async, fn, mc+4, "five", 30 ) } ;
    
    for( std::thread& t : threads ) t.join() ;
    for( auto& f : futures ) f.wait() ;
}
