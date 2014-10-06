#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

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

  // No-consuming case.
  { 
    std::cout << "Non-consuming example" << std::endl;
    boost::asio::streambuf streambuf;
    for (int i = 0; i < 5; ++i)
    {
      std::string data = "test";
      data += boost::lexical_cast<std::string>(i);
  
      // Write to server.
      std::size_t bytes_transferred =
          write(client_socket, boost::asio::buffer(data));
  
      // Read from client.
      read(server_socket, streambuf, 
           boost::asio::transfer_exactly(bytes_transferred));

      // Print results.
      std::string read_data(
        boost::asio::buffers_begin(streambuf.data()),
        boost::asio::buffers_end(streambuf.data()));
      std::cout << "size: " << streambuf.size() << ", "
                << "read: " << read_data << std::endl;
    }
  }
  
  // Consuming case.
  { 
    std::cout << "Consuming example" << std::endl;
    boost::asio::streambuf streambuf;
    for (int i = 0; i < 5; ++i)
    {
      std::string data = "test";
      data += boost::lexical_cast<std::string>(i);

      // Write to server.
      std::size_t bytes_transferred =
          write(client_socket, boost::asio::buffer(data));

      // Read from client.
      read(server_socket, streambuf, 
           boost::asio::transfer_exactly(bytes_transferred));

      // Print results.
      std::string read_data(
        boost::asio::buffers_begin(streambuf.data()),
        boost::asio::buffers_end(streambuf.data()));
      std::cout << "size: " << streambuf.size() << ", "
                << "read: " << read_data << std::endl;

      streambuf.consume(bytes_transferred);
    }
  }
}