#include <cassert>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

int main()
{
  boost::asio::io_service io_service;
  boost::asio::io_service::strand strand1(io_service);
  boost::asio::io_service::strand strand2(io_service);
  boost::asio::io_service::strand strand3(strand1);
  
  boost::asio::spawn(strand1,
    [&](boost::asio::yield_context yield)
    {
      assert(strand1.running_in_this_thread());
      assert(!strand2.running_in_this_thread());
      assert(strand3.running_in_this_thread());
      
      // Access implementation details.
      auto strand4 = yield.handler_.dispatcher_;
      assert(strand4.running_in_this_thread());
      
      // No way to compare strands to one another.  Although strand1, strand3,
      // and strand4 use the same strand implementation, there is no way to
      // compare the objects themselves to one another.
    });
    
  io_service.run();
}