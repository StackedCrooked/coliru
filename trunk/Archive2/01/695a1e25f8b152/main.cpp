#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// This example is not interested in the handlers, so provide a noop function
// that will be passed to bind to meet the handler concept requirements.
void noop() {}

std::string make_string(boost::asio::streambuf& streambuf)
{
 return {buffers_begin(streambuf.data()), 
         buffers_end(streambuf.data())};
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
  output << "a@"
            "b@";
  write(server_socket, write_buffer.data());
  std::cout << "Wrote: " << make_string(write_buffer) << std::endl;
  assert(write_buffer.size() == 4);  // Data not consumed.

  // Read from the client.
  boost::asio::streambuf read_buffer;
  
  // Demonstrate consuming via istream.
  {
    std::cout << "Read" << std::endl;
    auto bytes_transferred = read_until(client_socket, read_buffer, '@');
    // Verify that the entire write_buffer (data pass the first delimiter) was
    // read into read_buffer.
    auto initial_size = read_buffer.size();
    assert(initial_size == write_buffer.size());

    // Read from the streambuf.
    std::cout << "Read buffer contains: " << make_string(read_buffer)
              << std::endl;
    std::istream input(&read_buffer);
    std::string line;
    getline(input, line, '@'); // Consumes from the streambuf.
    assert("a" == line); // Note getline discards delimiter.
    std::cout << "Read consumed: " << line << "@" << std::endl;
    assert(read_buffer.size() == initial_size - bytes_transferred);
  }
  
  // Write an additional message to the server, but only consume 'a@'
  // from write buffer.  The buffer will contain 'b@c@'.
  write_buffer.consume(2);
  std::cout << "Consumed write buffer, it now contains: " <<
                make_string(write_buffer) << std::endl;
  assert(write_buffer.size() == 2);
  output << "c@";
  assert(write_buffer.size() == 4);
  write(server_socket, write_buffer.data());
  std::cout << "Wrote: " << make_string(write_buffer) << std::endl;
  
  // Demonstrate explicitly consuming via the streambuf.
  {
    std::cout << "Read" << std::endl;
    auto initial_size = read_buffer.size();
    auto bytes_transferred = read_until(client_socket, read_buffer, '@');
    // Verify that the read operation did not attempt to read data from
    // the socket, as the streambuf already contained the delimiter.
    assert(initial_size == read_buffer.size());
    
    // Read from the streambuf.
    std::cout << "Read buffer contains: " << make_string(read_buffer)
              << std::endl;
    std::string line(
        boost::asio::buffers_begin(read_buffer.data()),
        boost::asio::buffers_begin(read_buffer.data()) + bytes_transferred);
    assert("b@" == line);
    assert(read_buffer.size() == initial_size); // Nothing consumed.
    read_buffer.consume(bytes_transferred); // Explicitly consume.
    std::cout << "Read consumed: " << line << std::endl;
    assert(read_buffer.size() == 0);
  }
  
  // Read again.
  {
    std::cout << "Read" << std::endl;
    read_until(client_socket, read_buffer, '@');
    
    // Read from the streambuf.
    std::cout << "Read buffer contains: " << make_string(read_buffer)
              << std::endl;
    std::istream input(&read_buffer);
    std::string line;
    getline(input, line, '@'); // Consumes from the streambuf.
    assert("b" == line); // Note "b" is expected and not "c".
    std::cout << "Read consumed: " << line << "@" << std::endl;
    std::cout << "Read buffer contains: " << make_string(read_buffer)
              << std::endl;
  }
}