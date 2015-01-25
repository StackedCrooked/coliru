#include <iostream>
#include <chrono>
#include <string>
#include <thread>

int main()
{
    using clock = std::chrono::steady_clock ;
    using milliseconds = std::chrono::milliseconds ;

    const std::string str_msecs = std::to_string( std::chrono::duration_cast<milliseconds>(
                                                                clock::now().time_since_epoch() ).count() ) ;
                                                                
    const unsigned long long millisecs = std::stoll(str_msecs) ; // string => unsigned long long
    const milliseconds duration = milliseconds(millisecs) ; // unsigned long long => std::chrono::milliseconds
    const std::chrono::time_point<clock> time_pt(duration) ; // duration => time point of clock

    std::cout << std::chrono::duration_cast<milliseconds>( clock::now() - time_pt ).count() << '\n' ;
    std::this_thread::sleep_for( milliseconds(100) ) ;
    std::cout << std::chrono::duration_cast<milliseconds>( clock::now() - time_pt ).count() << '\n' ;
}
