#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// This example is not interested in the handlers, so provide a noop function
// that will be passed to bind to meet the handler concept requirements.
void noop() {}

/// @brief Helper function that extracts a string from a streambuf.
std::string make_string(
  boost::asio::streambuf& streambuf,
  std::size_t n)
{
  return std::string(
      boost::asio::buffers_begin(streambuf.data()),
      boost::asio::buffers_begin(streambuf.data()) + n);
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

  // Mockup write_buffer as if it read "xxxx@yyyy" with read_until()
  // using '@' as a delimiter.
  boost::asio::streambuf write_buffer;
  std::ostream output(&write_buffer);
  output << "xxxx@yyyy";
  assert(write_buffer.size() == 9);
  auto bytes_transferred = 5;

  // Write to server.
  boost::asio::write(server_socket, write_buffer,
      boost::asio::transfer_exactly(bytes_transferred));
   // Verify write operation consumed part of the input sequence.
  assert(write_buffer.size() == 4);

  // Read from client.
  boost::asio::streambuf read_buffer;
  bytes_transferred = boost::asio::read(
      client_socket, read_buffer.prepare(bytes_transferred));
  read_buffer.commit(bytes_transferred);

  // Copy from the read buffers input sequence.
  std::cout << "Read: " << 
               make_string(read_buffer, bytes_transferred) << std::endl;
  read_buffer.consume(bytes_transferred);

  // Mockup write_buffer as if it read "zzzz@kkkk" with read_until()
  // using '@' as a delimiter.
  output << "zzzz@kkkk";
  assert(write_buffer.size() == 13); 
  bytes_transferred = 9; // yyyyzzzz@

  // Write to server.
  boost::asio::write(server_socket, buffer(write_buffer.data(),
      bytes_transferred));
  // Verify write operation did not consume the input sequence.
  assert(write_buffer.size() == 13);
  write_buffer.consume(bytes_transferred);

  // Read from client.
  bytes_transferred = boost::asio::read(
      client_socket, read_buffer.prepare(bytes_transferred));
  read_buffer.commit(bytes_transferred);

  // Copy from the read buffers input sequence.
  std::cout << "Read: " << 
               make_string(read_buffer, bytes_transferred) << std::endl;
  read_buffer.consume(bytes_transferred);
}