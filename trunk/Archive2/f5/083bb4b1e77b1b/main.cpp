#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

void noop() {}

void print_status(
  const boost::system::error_code& error,
  std::size_t bytes_transferred)
{
  std::cout << "error = (" << error << ") " << error.message() << "; "
               "bytes_transferred = " << bytes_transferred
            << std::endl;
}

void run_io_service(std::string message, boost::asio::io_service& io_service)
{
  std::cout << message << ": ";
  io_service.run();
  io_service.reset();
}

int main()
{
  using boost::asio::ip::tcp;
  
  // Create all I/O objects.
  boost::asio::io_service io_service;
  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 0));
  tcp::socket socket1(io_service);
  tcp::socket socket2(io_service);

  // Connect the sockets.
  acceptor.async_accept(socket1, boost::bind(&noop));
  socket2.async_connect(acceptor.local_endpoint(), boost::bind(&noop));
  io_service.run();
  io_service.reset();

  const char data[] = "hello\n";
  char buffer[128];

  // Create an async receive operation and cancel it.
  socket1.async_receive(boost::asio::buffer(buffer), &print_status);
  socket1.cancel();
  run_io_service("async_receive1", io_service);

  // Create an async write operation.
  socket1.async_send(boost::asio::buffer(data), &print_status);
  run_io_service("async_send1", io_service);

  // Shutdown the receive side of the socket then create an async
  // receive operation.
  socket1.shutdown(tcp::socket::shutdown_receive);
  socket1.async_receive(boost::asio::buffer(buffer), &print_status);
  run_io_service("async_receive2", io_service);

  // Create an async write operation.
  socket1.async_send(boost::asio::buffer(data), &print_status);
  run_io_service("async_send2", io_service);
}