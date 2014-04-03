#include <iostream>
#include <boost/asio.hpp>

int main()
{
    boost::asio::io_service io_service;

    for (auto i = 0; i < 5; ++i)
        io_service.post([i]() { std::cout << i << std::endl; });

    std::cout << "stop()" << std::endl;
    io_service.stop();  
    std::cout << "reset()" << std::endl;
    io_service.reset();
    std::cout << "poll()" << std::endl;
    io_service.poll();
}