#include <iostream>
#include <memory>
#include "boost/asio.hpp"

struct Data
{
    Data()
		:
		socket(io)
	{
		socket.open(boost::asio::ip::udp::v4());
  		socket.bind({boost::asio::ip::udp::v4(), 12345U});
  		socket.set_option(boost::asio::socket_base::broadcast(true));
	}
	
	~Data()
    try
    {
        socket.shutdown(boost::asio::socket_base::shutdown_both);
        socket.close();
    }
    catch(std::exception &e)
    {
        std::cout << "unhandled exception: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "unknown unhandled exception" << std::endl;
    }
	
    boost::asio::io_service io;
    boost::asio::ip::udp::socket socket;
};

int main()
{
    std::unique_ptr<Data> data = std::make_unique<Data>(); // works
    data.reset(); // no error
    data = std::make_unique<Data>(); // exception thrown on bind
}
