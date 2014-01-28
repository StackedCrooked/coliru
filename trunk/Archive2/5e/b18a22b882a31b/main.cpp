#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

volatile long long v = 0 ;

int main()
{
    constexpr int N = 1024*1024*256 ;
    
    using namespace std::chrono ;
    const auto timepoint_start = steady_clock::now() ;         
    const auto clock_start = std::clock() ;
    
    std::this_thread::sleep_for( seconds(5) ) ;
    for( int i=0 ; i < N ; ++i ) v += 1 ;

    const auto clock_end = std::clock() ;
    const auto timepoint_end = steady_clock::now() ;         

    std::cout << "elapsed processor time: " << double(clock_end-clock_start) / CLOCKS_PER_SEC * 1000.0 << " milliseconds.\n" ;
    std::cout << "elapsed wall clock time: " << duration_cast<milliseconds>(timepoint_end-timepoint_start).count() << " milliseconds.\n" ;
}
