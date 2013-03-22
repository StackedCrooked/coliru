#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

using namespace boost::asio;

void
handleAccept(
    const boost::system::error_code& error,
    boost::shared_ptr<ip::tcp::socket> remote
    )
{
    if ( error ) {
        std::cerr << "Could not accept " << error.message() << std::endl;
        return;
    }
            
    std::cout << "accepted connection from " << remote->remote_endpoint() << std::endl;
}
   
void
handleConnect(
    const boost::system::error_code& error,
    boost::shared_ptr<ip::tcp::socket> local
    )
{
    if ( error ) {
        std::cerr << "Could not connect " << error.message() << std::endl;
        return;
    }
            
    std::cout << "connected to " << local->remote_endpoint() << std::endl;
}

int
main (int argc, char *argv[])
{
    io_service io_service;
    ip::tcp::acceptor acceptor( io_service,  ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 0) );
    std::cout << "listening on " << acceptor.local_endpoint() << std::endl;
    boost::shared_ptr<ip::tcp::socket> remote( new ip::tcp::socket(io_service) );
    acceptor.async_accept(
        *remote,
        boost::bind( &handleAccept, placeholders::error, remote )
        );
    
    boost::shared_ptr<ip::tcp::socket> local( new ip::tcp::socket(io_service) );
    local->async_connect(
        acceptor.local_endpoint(),
        boost::bind( &handleConnect, placeholders::error, local )
        );
        
    std::cout << "running" << std::endl;
    const size_t handlers = io_service.run();
    std::cout << "ran " << handlers << " handlers" << std::endl;
    
    return 0;
}