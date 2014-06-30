#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

void periodic_call( int period_in_milliseconds, int ntimes, std::function< void() > function  )  
{
    const auto period = std::chrono::milliseconds(period_in_milliseconds) ;
    std::chrono::milliseconds delta{} ;
    
    for( int i = 0 ; i < ntimes ; ++i )
    {
        std::this_thread::sleep_for( period - delta ) ;
        
        auto start = std::chrono::steady_clock::now() ;
        function() ;
        auto end = std::chrono::steady_clock::now() ;
        
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(end-start) ;
    }
}

void foo( int a, int b )
{
    static int n = 0 ;
    static int c = 0 ;
    
    c = c*a + b ;
    auto t = std::time(nullptr) ;
    char now[128] ;
    std::strftime( now, sizeof(now), "  at %c\n", std::localtime(&t) ) ;
    std::cout << ++n << ". " << c << now << std::flush ;
}

int main()
{
    // call foo(2,3) once every second, 7 times in all
    std::thread( periodic_call, 1000, 7, std::bind( foo, 2, 3 )  ).join() ;
}
