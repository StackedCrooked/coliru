#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// This example is not interested in the handlers, so provide a noop function
// that will be passed to bind to meet the handler concept requirements.
void noop() {}

std::string make_string(boost::asio::streambuf& streambuf)
{
  return {boost::asio::buffers_begin(streambuf.data()), 
          boost::asio::buffers_end(streambuf.data())};
}

int main()
{
  using boost::asio::ip::tcp;
  boost::asio::io_service io_service;

  // Create all I/O objects.
  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 0));
  tcp::socket server_socket(io_service);
  tcp::socket client_socket(io_service);

  // Connect client and server sockets.
  acceptor.async_accept(server_socket, boost::bind(&noop));
  client_socket.async_connect(acceptor.local_endpoint(), boost::bind(&noop));
  io_service.run();

  // Write to server.
  boost::asio::streambuf write_buffer;
  std::ostream output(&write_buffer);
  output << "abc";
  std::cout << "Writing: " << make_string(write_buffer) << std::endl;
  auto bytes_transferred = boost::asio::write(server_socket, write_buffer);
  
  // Read from client.
  boost::asio::streambuf read_buffer;
  bytes_transferred = boost::asio::read(client_socket, read_buffer,
      boost::asio::transfer_exactly(bytes_transferred));
  std::cout << "Read: " << make_string(read_buffer) << std::endl;
  read_buffer.consume(bytes_transferred); // Remove data that was read.
  
  // Write to server.
  output << "def";
  std::cout << "Writing: " << make_string(write_buffer) << std::endl;
  bytes_transferred = boost::asio::write(server_socket, write_buffer);
  
  // Read from client.
  bytes_transferred = boost::asio::read(client_socket, 
      read_buffer.prepare(bytes_transferred));
  read_buffer.commit(bytes_transferred);      
  std::cout << "Read: " << make_string(read_buffer) << std::endl;
  read_buffer.consume(bytes_transferred); // Remove data that was read.
}