#include <boost/coroutine/all.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
	boost::asio::io_service io_service;
	boost::asio::spawn
	(
		io_service,
		[&](boost::asio::yield_context yield)
		{
            std::cout << "Entering coroutine" << std::endl;
			try
			{
				boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::atoi(argv[1])));
				for (;;)
				{
					boost::system::error_code ec;
					boost::asio::ip::tcp::socket socket(io_service);

					acceptor.async_accept(socket, yield[ec]);
				};
			}
			catch (...)
			{
                std::cout << "Exiting coroutine" << std::endl;
				throw;
			}
		}
	);

	for (int i = 0; i != 10; ++i)
	{
		io_service.poll_one();
	}
}
