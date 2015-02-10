#include <functional>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/iostreams/concepts.hpp>  // boost::iostreams::source
#include <boost/iostreams/stream.hpp>

/// Type that implements a model of the Boost.IOStream's Source concept
/// for reading data from a Boost.Asio streambuf
class asio_streambuf_input_device
  : public boost::iostreams::source // Use convenience class.
{
public:

  explicit
  asio_streambuf_input_device(
      boost::asio::streambuf& streambuf,
      std::string delim,
      std::streamsize bytes_transferred
  )
    : streambuf_(streambuf),
      delim_size_(delim.size()),
      bytes_remaining_(bytes_transferred - delim_size_)
  {}

  std::streamsize read(char_type* buffer, std::streamsize buffer_size) 
  {
    // Determine max amount of bytes to copy.
    auto bytes_to_copy = 
      std::min(bytes_remaining_, std::min(
          static_cast<std::streamsize>(streambuf_.size()), buffer_size));
    
    // If there is no more data to be read, indicate end-of-sequence per
    // Source concept.
    if (0 == bytes_to_copy)
    {
      return -1; // Indicate end-of-sequence, per Source concept.
    }
    
    // Copy from the streambuf into the provided buffer.
    std::copy_n(buffers_begin(streambuf_.data()), bytes_to_copy, buffer);
    
    // Update bytes remaining.
    bytes_remaining_ -= bytes_to_copy;
    
    // Determine how many bytes to consume.
    auto bytes_to_consume = bytes_to_copy; 
    
    // If there are no more bytes remaining, then consume to the delimiter.
    if (0 == bytes_remaining_)
    {
      bytes_to_consume += delim_size_;
    }
    // Consume from the streambuf.
    streambuf_.consume(bytes_to_consume);
    
    return bytes_to_copy;
  }

private:
  boost::asio::streambuf& streambuf_;
  std::size_t delim_size_;
  std::streamsize bytes_remaining_;
};

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
  acceptor.async_accept(server_socket, std::bind(&noop));
  client_socket.async_connect(acceptor.local_endpoint(), std::bind(&noop));
  io_service.run();
  
  // Write to server.
  std::string message = "12345\nsome bad next frame\n";
  write(server_socket, boost::asio::buffer(message));
  
  // Read from the client.
  boost::asio::streambuf streambuf;
  auto bytes_transferred = read_until(client_socket, streambuf, '\n');
  
  // Guarantee that the entire message was read.
  assert(bytes_transferred < streambuf.size());
  assert(message.size() == streambuf.size());
  
  // Create a custom iostream that sets a limit on the amount of bytes
  // that will be read.
  boost::iostreams::stream<asio_streambuf_input_device> input(
      streambuf, "\n", bytes_transferred);
      
  // Read 12345.
  int data = 0;
  input >> data;
  assert(data == 12345);
  assert(streambuf.size() < message.size()); // Verify data was consumed.
  
  // Attempt to read.
  const auto size_before_getline = streambuf.size();
  assert(size_before_getline > 0); // Verify the streambuf still has data.
  std::string extra;
  getline(input, extra);
  assert(extra.empty());
  assert(input.eof());
  assert(size_before_getline == streambuf.size()); // Verify nothing was read.
}
