#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>

void demo_deferred_completion()
{
  std::cout << "[demo deferred completion]" << std::endl;
  boost::asio::io_service io_service;
  auto wait_completed = false;

  // Use scope to force lifetime.  
  {
    // Create the timer and initiate an async_wait operation that
    // is guaranteed to have expired.
    boost::asio::steady_timer timer(io_service);

    // Post a ready-to-run no-op completion handler into the io_service.
    // Although the order is unspecified, the current implementation
    // will use a predictable order.
    io_service.post([]{});

    // Initiate an async_wait operation that will immediately expire.
    timer.expires_at(boost::asio::steady_timer::clock_type::now());
    timer.async_wait(
        [&](const boost::system::error_code& error)
        {
          std::cout << "error: " << error.message() << std::endl;
          assert(error == boost::system::error_code()); // Success.
          wait_completed = true;          
        });

    // While this will only run one handler (the noop), it will
    // execute operations (async_wait), and if they are succesful
    // (time expired), the completion handler will be posted for
    // deferred completion.
    io_service.run_one();
    assert(!wait_completed); // Verify the wait handler was not invoked.
  } // Destroy the timer.

  // Run the handle_wait completion handler.
  io_service.run();
  assert(wait_completed);
}

void demo_cancelled()
{
  std::cout << "[demo cancelled]" << std::endl;
  boost::asio::io_service io_service;

  // Use scope to force lifetime.
  {
    boost::asio::steady_timer timer(io_service);

    // Initiate an async_wait operation that will immediately expire.
    timer.expires_at(boost::asio::steady_timer::clock_type::now());
    timer.async_wait(
        [](const boost::system::error_code& error)
        {
          std::cout << "error: " << error.message() << std::endl;
          assert(error ==
                 make_error_code(boost::asio::error::operation_aborted));
        });
  } // Destroy the timer.

  // Run the handle_wait completion handler.
  io_service.run();
}

int main()
{
  demo_deferred_completion();
  demo_cancelled();
}