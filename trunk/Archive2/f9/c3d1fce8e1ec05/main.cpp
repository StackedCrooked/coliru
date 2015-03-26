#include <chrono>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

// Mockup model.
class Foo {};

// Mockup serializer.
void store_state(Foo& foo)
{
  // ... serialize state with Boost.Serialization ...
  // ... persists state, perhaps to the filesystem or a
  //     message queue
  std::cout << "Storing state" << std::endl;
}

int main()
{
  bool running = true;
  Foo foo;

  // Setup signal handling.
  boost::asio::io_service io_service;
  boost::asio::signal_set signals(io_service);
  signals.add(SIGUSR1);
  signals.async_wait([&running, &foo](
      const boost::system::error_code& error,
      int signal_number) 
    {
      // On error, return early.
      if (error) return;
      std::cout << "Handling SIGUSR1: " 
                << std::boolalpha << (SIGUSR1 == signal_number)
                << std::noboolalpha << std::endl;

      // Set flag to allow graceful exit.
      running = false;

      // Store the state.
      store_state(foo);
    });

  // Main work loop.
  while (running)
  {
    std::cout << "Busy work" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    io_service.poll(); // Handle signals.
  }
  std::cout << "Finish" << std::endl;
}