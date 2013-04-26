#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

void
foo(
    boost::asio::serial_port* port
    )
{
    
}

void
bar(
    boost::asio::serial_port& port
    )
{
    
}
int main() {
    boost::asio::io_service ios;
    boost::asio::serial_port port(ios);
    boost::thread t1(foo, &port);
    boost::thread t2(bar, boost::ref(port));
    t1.join();
    t2.join();
    
    return 0;
}