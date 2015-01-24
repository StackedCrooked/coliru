#include <iostream>
#include <chrono>
#include <string>
#include <thread>

int main()
{
    using namespace std::chrono ;
    const auto time_pt = steady_clock::now() ;
    const auto milliseconds_since_epoch_begin = duration_cast<milliseconds>( time_pt.time_since_epoch() ).count() ;
    const std::string str = std::to_string(milliseconds_since_epoch_begin) + " milliseconds." ;
    std::cout << str << '\n' ;
    
    std::this_thread::sleep_for( seconds(2) ) ;
    std::cout << duration_cast<milliseconds>( steady_clock::now().time_since_epoch() ).count() << " milliseconds.\n" ;
}
