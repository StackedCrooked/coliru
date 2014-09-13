#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void foo( int secs, int id )
{
    std::this_thread::sleep_for( std::chrono::seconds(secs) ) ;
    std::cout << id << " - done\n" << std::flush ;
}

int main()
{
    std::size_t n = 10 ;
    std::vector<std::thread> threads ;
    threads.reserve(n) ;
    
    for( std::size_t i = 0 ; i < n ; ++i ) threads.emplace_back( foo, i%3, i ) ;
    
    for( auto& t : threads ) t.join() ;
}
