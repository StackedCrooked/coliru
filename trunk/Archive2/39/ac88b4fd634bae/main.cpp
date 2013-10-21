#include <iostream>
#include <chrono>
#include <thread>
 
int main()
{
    std::cout << "Hello waiter" << std::endl;
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    std::cout << "Waited 2000 ms\n";
    std::chrono::milliseconds dura4( 4000 );
    std::this_thread::sleep_for( dura4 );
    std::cout << "Waited 4000 ms\n";
}