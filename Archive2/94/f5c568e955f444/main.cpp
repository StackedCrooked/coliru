#include <iostream>
#include <functional>

#include <boost/asio.hpp>

void handle_accept(const boost::system::error_code& error_code)
{
  std::cout << "handle_accept: " << error_code.message() << std::endl;
}

void noop() {}

int main()
{
  using boost::asio::ip::tcp;
  boost::asio::io_service io_service;

  // Create all I/O objects.
  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 0));
  tcp::socket server_socket(io_service);
  tcp::socket client_socket(io_service);

  // Connect client and server sockets.
  acceptor.async_accept(server_socket, std::bind(&handle_accept,
    std::placeholders::_1 /* error_code */));
  client_socket.async_connect(acceptor.local_endpoint(), std::bind(&noop));
  io_service.run();
}