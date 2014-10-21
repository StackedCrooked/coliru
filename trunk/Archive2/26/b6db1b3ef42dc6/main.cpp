#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>

#include <iostream>
using namespace std;

int main ()
{
  using namespace boost::asio;

  io_service io;

  spawn (io, [&] (yield_context yield) {
    cout << "main coro starts\n";

    auto lambda = [&] (yield_context yield)
      {
        cout << "in lambda inside subcoroutine - starts\n";
        steady_timer t (io, std::chrono::seconds (1));
        t.async_wait (yield);
        cout << "in lambda inside subcoroutine - finishes\n";
      };
      
    // starting few coroutines
    spawn (yield, lambda);
    spawn (yield, lambda);

    // now I want to wait for all of them to finish before I do
    // some other work?
    // ???
    
    cout << "main coro finishes\n";
  });

  io.run ();
}