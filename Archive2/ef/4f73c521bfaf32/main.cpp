#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <ctime>

void timer( int msecs, int nticks, std::function< void() > call_back )
{
    for( int i = 0 ; i < nticks ; ++i )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds(msecs) ) ;
        call_back() ; // assumes that callback returns almost immediately
    }
}

void foo() 
{
    char cstr[1024] ;
    auto t = std::time(nullptr) ;
    std::strftime( cstr, sizeof(cstr), "%T", std::localtime(&t) ) ;
    std::cout << cstr << " tick" << std::endl ; 
}

int main()
{
    std::thread thread( timer, 1000, 7, foo ) ;
    std::cout << "started timer" << std::endl ;
    std::this_thread::sleep_for( std::chrono::seconds(3) ) ;
    std::cout << "waiting for timer to finish" << std::endl ;
    thread.join() ;
    std::cout << "done\n" ;
}
