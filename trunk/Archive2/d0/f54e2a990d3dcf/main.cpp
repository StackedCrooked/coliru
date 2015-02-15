#include <functional>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

/// @brief Type that derives from Boost.Asio streambuf and can frame the
///        input sequence to a portion of the actual input sequence.
template <typename Allocator = std::allocator<char> >
class basic_framed_streambuf
  : public boost::asio::basic_streambuf<Allocator>
{
private:

  typedef boost::asio::basic_streambuf<Allocator> parent_type;

public:

  explicit 
  basic_framed_streambuf(
    std::size_t maximum_size = (std::numeric_limits< std::size_t >::max)(),
    const Allocator& allocator = Allocator()
  )
    : parent_type(maximum_size, allocator),
      egptr_(nullptr)
  {}

  /// @brief Limit the current input sequence to n characters.
  ///
  /// @remark An active frame is invalidated by any member function that
  ///        modifies the input or output sequence.
  void frame(std::streamsize n)
  {
    // Store actual end of input sequence.
    egptr_ = this->egptr();
    // Set the input sequence end to n characters from the current
    // input sequence pointer..
    this->setg(this->eback(), this->gptr(), this->gptr() + n);
  }

  /// @brief Restore the end of the input sequence.
  void unframe()
  {
    // Restore the end of the input sequence.
    this->setg(this->eback(), this->gptr(), this->egptr_);
    egptr_ = nullptr;
  }

protected:

  // When the end of the input sequence has been reached, underflow
  // will be invoked.
  typename parent_type::int_type underflow()
  {
    // If the  streambuf is currently framed, then return eof
    // on underflow.  Otherwise, defer to the parent implementation.
    return egptr_ ? parent_type::traits_type::eof()
                  : parent_type::underflow();
  }

private:
  char* egptr_;
};

typedef basic_framed_streambuf<> framed_streambuf;

/// @brief RAII type that helps frame a basic_framed_streambuf within a 
///        given scope.
template <typename Streambuf>
class streambuf_frame
{
public:
  explicit streambuf_frame(Streambuf& streambuf, std::streamsize n)
    : streambuf_(streambuf)
  {
    streambuf_.frame(n);
  }

  ~streambuf_frame() { streambuf_.unframe(); }

  streambuf_frame(const streambuf_frame&) = delete;
  streambuf_frame& operator=(const streambuf_frame&) = delete;

private:
  Streambuf& streambuf_;
};

/// @brief Convert a streambuf to a string.
std::string make_string(boost::asio::streambuf& streambuf)
{
  return std::string(buffers_begin(streambuf.data()),
                     buffers_end(streambuf.data()));
}

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

  // Write to client.
  const std::string message =
    "12@"
    "345@";
  write(server_socket, boost::asio::buffer(message));

  framed_streambuf streambuf;

  // Demonstrate framing the streambuf's input sequence manually.
  {
    auto bytes_transferred = read_until(client_socket, streambuf, '@');
    // Verify that the entire message "12\0345\06789\0" was read into
    // streambuf's input sequence.
    assert(message.size() == streambuf.size());
    std::cout << "streambuf contains: " << make_string(streambuf) <<
                  std::endl;

    // Frame the streambuf based on bytes_transferred.  This is all data
    // up to and including the first delimiter.
    streambuf.frame(bytes_transferred);

    // Use an istream to read data from the currently framed streambuf.
    std::istream input(&streambuf);
    int data = 0;
    input >> data; // Consumes "123" from input sequence.
    assert(data == 12);
    std::cout << "Extracted " << data << std::endl;
    assert(!input.eof());
    input.get(); // Consume "@" from input sequence.
    assert(!input.eof());
    input.get(); // No more data available in the frame, so underflow.
    assert(input.eof());
    std::cout << "istream has reached EOF" << std::endl;

    // Restore the streambuf.
    streambuf.unframe();
    assert(streambuf.size() == message.size() - 3);
  }

  // Demonstrate using an RAII helper to frame the streambuf's input
  // sequence.
  {
    // As the streambuf's input sequence already contains the delimiter,
    // this operation will not actually attempt to read data from the
    // socket.
    auto bytes_transferred = read_until(client_socket, streambuf, '@');
    std::cout << "streambuf contains: " << make_string(streambuf) <<
                  std::endl;

    // Frame the streambuf based on bytes_transferred.  This is all data
    // up to and including the first delimiter.  Use a frame RAII object
    // to only frame the streambuf within the current scope.
    streambuf_frame<framed_streambuf> frame(streambuf, bytes_transferred);

    // Use an istream to read data from the currently framed streambuf.
    std::istream input(&streambuf);
    std::string data;
    getline(input, data, '@'); // Consumes delimiter.
    assert(data == "345");
    std::cout << "Extracted " << data << std::endl;
    assert(!input.eof());
    input.get(); // No more data available in the frame, so underflow.
    assert(input.eof());
    std::cout << "istream has reached EOF" << std::endl;
    // The frame object's destructor will unframe the streambuf.
  }

  assert(streambuf.size() == 0);
  std::cout << "streambuf is empty" << std::endl;
}