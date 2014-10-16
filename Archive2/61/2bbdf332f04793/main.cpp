#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/bind.hpp>

void noop() {}

/// @brief Handler that will print the actual error and assert 
///        with the expected error.
void handle_wait(
  const boost::system::error_code& actual_error,
  boost::system::error_code expected_error)
{
  std::cout << "error: " << actual_error.message() << std::endl;
  assert(actual_error == expected_error);
}

void demo_deferred_completion()
{
  std::cout << "[demo deferred completion]" << std::endl;
  boost::asio::io_service io_service;

  // Use scope to force lifetime.
  {
    // Create the timer and initiate an async_wait operation that
    // is guaranteed to have expired.
    boost::asio::steady_timer timer(io_service);

    // Post a ready-to-run completion handler into the io_service.
    // Although the order is unspecified, the current implementation
    // will use a predictable order.
    io_service.post(&noop);

    // Initiate an async_wait operation that will immediately expire.
    timer.expires_at(boost::asio::steady_timer::clock_type::now());
    timer.async_wait(boost::bind(&handle_wait,
        boost::asio::placeholders::error,
        boost::system::error_code()));

    // While this will only run one handler (the noop), it will
    // execute operations (async_wait), and if they are succesful
    // (time expired), the completion handler will be posted for
    // deferred completion.
    io_service.run_one();
  } // Destroy the timer.

  // Run the handle_wait completion handler.
  io_service.run();
}

void demo_cancelled()
{
  std::cout << "[demo cancelled completion]" << std::endl;
  boost::asio::io_service io_service;

  // Use scope to force lifetime.
  {
    boost::asio::steady_timer timer(io_service);

    // Initiate an async_wait operation that will immediately expire.
    timer.expires_at(boost::asio::steady_timer::clock_type::now());
    timer.async_wait(boost::bind(&handle_wait,
        boost::asio::placeholders::error,
        make_error_code(boost::asio::error::operation_aborted)));
  } // Destroy the timer.

  // Run the handle_wait completion handler.
  io_service.run();
}

int main()
{
  demo_deferred_completion();
  demo_cancelled();
}