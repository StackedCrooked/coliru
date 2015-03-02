#include <cstdio>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

/// @brief server demonstrates using domain sockets to accept
///        and read from a connection.
class server
{
public:
  server(
    boost::asio::io_service& io_service,
    const std::string& file)
    : io_service_(io_service),
      acceptor_(io_service_, 
        boost::asio::local::stream_protocol::endpoint(file)),
      client_(io_service_)
  {
    std::cout << "start accepting connection" << std::endl;
    acceptor_.async_accept(client_,
      boost::bind(&server::handle_accept, this,
        boost::asio::placeholders::error));
  }

private:

  void handle_accept(const boost::system::error_code& error)
  {
    std::cout << "handle_accept: " << error.message() << std::endl;
    if (error) return;

    std::cout << "start reading" << std::endl;
    client_.async_read_some(boost::asio::buffer(buffer_),
      boost::bind(&server::handle_read, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
  }

  void handle_read(
    const boost::system::error_code& error,
    std::size_t bytes_transferred)
  {
    std::cout << "handle_read: " << error.message() << std::endl;
    if (error) return;

    std::cout << "read: ";
    std::cout.write(buffer_.begin(), bytes_transferred);
    std::cout.flush();
  }

private:
  boost::asio::io_service& io_service_;
  boost::asio::local::stream_protocol::acceptor acceptor_;
  boost::asio::local::stream_protocol::socket client_;
  std::array<char, 1024> buffer_;
};

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: <file>\n";
    return 1;
  }

  // Remove file on startup and exit.
  std::string file(argv[1]);
  struct file_remover
  {
    file_remover(std::string file): file_(file) { std::remove(file.c_str()); }
    ~file_remover() { std::remove(file_.c_str()); }
    std::string file_;
  } remover(file);

  // Create and run the server.
  boost::asio::io_service io_service;
  server s(io_service, file);
  io_service.run();
}