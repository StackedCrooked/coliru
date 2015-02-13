#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// This example is not interested in the handlers, so provide a noop function
// that will be passed to bind to meet the handler concept requirements.
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
  acceptor.async_accept(server_socket, boost::bind(&noop));
  client_socket.async_connect(acceptor.local_endpoint(), boost::bind(&noop));
  io_service.run();

  // Write to server.
  boost::asio::streambuf write_buffer;
  std::ostream output(&write_buffer);
  output << "a\r\n"
            "b\r\n";
  write(server_socket, write_buffer.data());
  assert(write_buffer.size() == 6);  // Data not consumed.

  // Read from the client.
  boost::asio::streambuf read_buffer;
  
  // Demonstrate consuming via istream.
  {
    auto bytes_transferred = read_until(client_socket, read_buffer, "\r\n");
    // Verify that the entire write_buffer (data pass the first delimiter) was
    // read into read_buffer.
    auto initial_size = read_buffer.size();
    assert(initial_size == write_buffer.size());
    
    // Read from the streambuf.
    std::istream input(&read_buffer);
    std::string line;
    std::getline(input, line); // Consumes from the streambuf.
    assert("a\r" == line); // Note getline discards default delimiter '\n'.
    assert(read_buffer.size() == initial_size - bytes_transferred);
  }
  
  // Write an additional message to the server, but only consume 'a\r\n'
  // from write buffer.  The buffer will contain 'b\r\nc\r\n'.
  write_buffer.consume(3);
  assert(write_buffer.size() == 3);
  output << "c\r\n";
  assert(write_buffer.size() == 6);
  write(server_socket, write_buffer.data());
  
  // Demonstrate explicitly consuming via the streambuf.
  {
    auto initial_size = read_buffer.size();
    auto bytes_transferred = read_until(client_socket, read_buffer, "\r\n");
    // Verify that the read operation did not attempt to read data from the socket,
    // as the streambuf already contained the delimiter.
    assert(initial_size == read_buffer.size());
    
    // Read form the streambuf.
    std::string line(
        boost::asio::buffers_begin(read_buffer.data()),
        boost::asio::buffers_begin(read_buffer.data()) + bytes_transferred);
    assert("b\r\n" == line);
    assert(read_buffer.size() == initial_size); // Nothing consumed.
    read_buffer.consume(bytes_transferred); // Explicitly consume.
    assert(read_buffer.size() == 0);
  }
  
  // Read again.
  {
    read_until(client_socket, read_buffer, "\r\n");
    
    // Read from the streambuf.
    std::istream input(&read_buffer);
    std::string line;
    std::getline(input, line); // Consumes from the streambuf.
    assert("b\r" == line); // Note "b\r" is expected and not "c\r".
  }
}