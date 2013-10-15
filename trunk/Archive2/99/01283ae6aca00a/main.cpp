#include <iostream>
#include <chrono>
#include <thread>

std::ostream& operator<<(std::ostream& os, std::chrono::milliseconds ms)
{
    return os << ms.count() << " ms";
}
 
int main()
{
    std::cout << "Hello waiter" << std::endl;
    std::chrono::milliseconds dura( 50 );
    std::this_thread::sleep_for( dura );
    std::cout << "Waited " << dura;
}