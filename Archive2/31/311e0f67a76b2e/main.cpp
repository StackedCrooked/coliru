#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>

void foo(boost::asio::steady_timer& timer, boost::asio::yield_context yield)
{
  std::cout << "Enter foo" << std::endl;

  timer.expires_from_now(
      boost::asio::steady_timer::clock_type::duration::max());
  boost::system::error_code error;
  timer.async_wait(yield[error]);
  std::cout << "foo error: " << error.message() << std::endl;

  std::cout << "Leave foo" << std::endl;
}

void bar(
  boost::asio::io_service::strand& strand,
  boost::asio::steady_timer& timer
)
{
  std::cout << "Enter bar" << std::endl;

  // Wait a little for asio::io_service::run to be executed
  std::this_thread::sleep_for(std::chrono::seconds(1));
  // Post timer cancellation into the strand.
  strand.post([&timer]()
    {
      timer.cancel();
    });

  std::cout << "Leave bar" << std::endl;
}

int main()
{
  boost::asio::io_service io_service;
  boost::asio::steady_timer timer(io_service);
  boost::asio::io_service::strand strand(io_service);

  // Use an explicit strand, rather than having the io_service create.
  boost::asio::spawn(strand, std::bind(&foo, 
      std::ref(timer), std::placeholders::_1));

  // Pass the same strand to the thread, so that the thread may post
  // handlers synchronized with the foo coroutine.
  std::thread t(&bar, std::ref(strand), std::ref(timer));

  io_service.run();
  t.join();
}