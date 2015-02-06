#include <array>
#include <functional>
#include <iostream>
#include <thread>

#include <boost/asio.hpp>

void noop() {}

int main()
{
  boost::asio::io_service io_service;

  // Create two connected sockets.
  boost::asio::local::stream_protocol::socket sender(io_service);
  boost::asio::local::stream_protocol::socket receiver(io_service);
  connect_pair(sender, receiver);
  
  // Start async read.
  std::array<char, 1> async_receive_buffer;
  receiver.async_read_some(boost::asio::buffer(async_receive_buffer), std::bind(&noop));
  
  // Run the io_service.
  std::thread async_read_thread([&](){ io_service.run(); });
  
  // Start a sync read.
  std::array<char, 1> sync_receive_buffer;  
  std::thread sync_read_thread([&]()
    {
      read(receiver, boost::asio::buffer(sync_receive_buffer));
      std::cout << "sync receive got: " << sync_receive_buffer[0] << std::endl; 
    });
  
  // Allow time for threads to startup.
  std::string message = "AB";
  std::this_thread::sleep_for(std::chrono::seconds(3));
  write(sender, boost::asio::buffer(message));
  
  // Cleanup.
  sync_read_thread.join();
  async_read_thread.join();
}
