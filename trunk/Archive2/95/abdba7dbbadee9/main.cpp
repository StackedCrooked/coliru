#include <cassert>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

class client
{
public:

  // This demo is only using status for asserting code paths.  It is not
  // necessary nor should it be used for conditional branching.
  enum status_type
  {
    unknown,
    timeout,
    read_success,
    read_failure
  };

public:
  client(boost::asio::ip::tcp::socket& socket)
    : strand_(socket.get_io_service()),
      timer_(socket.get_io_service()),
      socket_(socket),
      status_(unknown)
  {}

  status_type status() const { return status_; }

  void async_read_with_timeout(boost::posix_time::seconds seconds)
  {
    strand_.post(boost::bind(
        &client::do_async_read_with_timeout, this, seconds));
  }

private:

  void do_async_read_with_timeout(boost::posix_time::seconds seconds)
  {
    // Start a timeout for the read.
    timer_.expires_from_now(seconds);
    timer_.async_wait(strand_.wrap(boost::bind(
        &client::handle_wait, this,
        boost::asio::placeholders::error)));

    // Start the read operation.
    boost::asio::async_read(socket_,  
        boost::asio::buffer(buffer_),
        strand_.wrap(boost::bind(
          &client::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)));
  }

  void handle_wait(const boost::system::error_code& error)
  {
    // On error, such as cancellation, return early.
    if (error)
    {
      std::cout << "timeout cancelled" << std::endl;
      return;
    }

    // The timer may have expired, but it is possible that handle_read()
    // ran succesfully and updated the timer's expiration:
    // - a new timeout has been started.  For example, handle_read() ran and
    //   invoked do_async_read_with_timeout().
    // - there are no pending timeout reads.  For example, handle_read() ran
    //   but did not invoke do_async_read_with_timeout();
    if (timer_.expires_at() > boost::asio::deadline_timer::traits_type::now())
    {
      std::cout << "timeout occured, but handle_read ran first" << std::endl;
      return;
    }

    // Otherwise, a timeout has occured and handle_read() has not executed, so
    // close the socket, cancelling the read operation.
    std::cout << "timeout occured" << std::endl;
    status_ = client::timeout;
    boost::system::error_code ignored_ec;
    socket_.close(ignored_ec);
  }

  void handle_read(
    const boost::system::error_code& error,
    std::size_t bytes_transferred)
  {
    // Update timeout state to indicate handle_read() has ran.  This
    // cancels any pending timeouts.
    timer_.expires_at(boost::posix_time::pos_infin);

    // On error, return early.
    if (error)
    {
      std::cout << "read failed: " << error.message() << std::endl;
      // Only set status if it is unknown.
      if (client::unknown == status_) status_ = client::read_failure;
      return;
    }

    // The read was succesful, but if a timeout occured and handle_wait()
    // ran first, then the socket is closed, so return early.
    if (!socket_.is_open())
    {
      std::cout << "read was succesful but timeout occured" << std::endl;
      return;
    }

    std::cout << "read was succesful" << std::endl;
    status_ = client::read_success;
  }

private:
  boost::asio::io_service::strand strand_;
  boost::asio::deadline_timer timer_;
  boost::asio::ip::tcp::socket& socket_;
  char buffer_[1];
  status_type status_;
};

// This example is not interested in the connect handlers, so provide a noop
// function that will be passed to bind to meet the handler concept
// requirements.
void noop() {}

/// @brief Create a connection between the server and client socket.
void connect_sockets(
  boost::asio::ip::tcp::acceptor& acceptor,
  boost::asio::ip::tcp::socket& server_socket,
  boost::asio::ip::tcp::socket& client_socket)
{
  boost::asio::io_service& io_service = acceptor.get_io_service();
  acceptor.async_accept(server_socket, boost::bind(&noop));
  client_socket.async_connect(acceptor.local_endpoint(), boost::bind(&noop));
  io_service.reset();
  io_service.run();
  io_service.reset();
}

int main()
{
  using boost::asio::ip::tcp;
  boost::asio::io_service io_service;
  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 0));

  // Scenario 1: timeout
  // The server writes no data, causing a client timeout to occur.
  {
    std::cout << "[Scenario 1: timeout]" << std::endl;
    // Create and connect I/O objects.
    tcp::socket server_socket(io_service);
    tcp::socket client_socket(io_service);
    connect_sockets(acceptor, server_socket, client_socket);

    // Start read with timeout on client.
    client client(client_socket);
    client.async_read_with_timeout(boost::posix_time::seconds(0));

    // Allow do_read_with_timeout to intiate actual operations.
    io_service.run_one();    

    // Run timeout and read operations.
    io_service.run();
    assert(client.status() == client::timeout);
  }

  // Scenario 2: no timeout, succesful read
  // The server writes data and the io_service is ran before the timer 
  // expires.  In this case, the async_read operation will complete and
  // cancel the async_wait.
  {
    std::cout << "[Scenario 2: no timeout, succesful read]" << std::endl;
    // Create and connect I/O objects.
    tcp::socket server_socket(io_service);
    tcp::socket client_socket(io_service);
    connect_sockets(acceptor, server_socket, client_socket);

    // Start read with timeout on client.
    client client(client_socket);
    client.async_read_with_timeout(boost::posix_time::seconds(10));

    // Allow do_read_with_timeout to intiate actual operations.
    io_service.run_one();

    // Write to client.
    boost::asio::write(server_socket, boost::asio::buffer("test"));

    // Run timeout and read operations.
    io_service.run();
    assert(client.status() == client::read_success);
  }

  // Scenario 3: no timeout, failed read
  // The server closes the connection before the timeout, causing the
  // async_read operation to fail and cancel the async_wait operation.
  {
    std::cout << "[Scenario 3: no timeout, failed read]" << std::endl;
    // Create and connect I/O objects.
    tcp::socket server_socket(io_service);
    tcp::socket client_socket(io_service);
    connect_sockets(acceptor, server_socket, client_socket);

    // Start read with timeout on client.
    client client(client_socket);
    client.async_read_with_timeout(boost::posix_time::seconds(10));

    // Allow do_read_with_timeout to intiate actual operations.
    io_service.run_one();

    // Close the socket.
    server_socket.close();

    // Run timeout and read operations.
    io_service.run();
    assert(client.status() == client::read_failure);
  }

  // Scenario 4: timeout and read success
  // The server writes data, but the io_service is not ran until the
  // timer has had time to expire.  In this case, both the await_wait and
  // asnyc_read operations complete, but the order in which the
  // handlers run is indeterminiate.
  {
    std::cout << "[Scenario 4: timeout and read success]" << std::endl;
    // Create and connect I/O objects.
    tcp::socket server_socket(io_service);
    tcp::socket client_socket(io_service);
    connect_sockets(acceptor, server_socket, client_socket);

    // Start read with timeout on client.
    client client(client_socket);
    client.async_read_with_timeout(boost::posix_time::seconds(0));

    // Allow do_read_with_timeout to intiate actual operations.
    io_service.run_one();

    // Allow the timeout to expire, the write to the client, causing both
    // operations to complete with success.
    boost::this_thread::sleep_for(boost::chrono::seconds(1));
    boost::asio::write(server_socket, boost::asio::buffer("test"));

    // Run timeout and read operations.
    io_service.run();
    assert(   (client.status() == client::timeout)
           || (client.status() == client::read_success));
  }
}