#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>

#include <iostream>
using namespace std;

int main ()
{
  using namespace boost::asio;

  io_service io;

  spawn (io, [&] (yield_context yield) {
    cout << "main coro starts\n";


    steady_timer rendez_vous (io, steady_timer::clock_type::duration::max ());
    volatile int counter = 2;


    auto lambda = [&] (yield_context yield)
      {
        cout << "in lambda inside subcoroutine - starts\n";
        steady_timer t (io, boost::chrono::seconds (1));
        t.async_wait (yield);
        cout << "in lambda inside subcoroutine - finishes\n";
        
        if (--counter == 0)
            rendez_vous.cancel ();
      };

    // starting few coroutines
    spawn (yield, lambda);
    spawn (yield, lambda);

    // now I want to wait for all of them to finish before I do
    // some other work?
    // ???
    boost::system::error_code ec;
    rendez_vous.async_wait (yield [ec]);
    // ignore errors here by reason.

    cout << "main coro finishes\n";
  });

  io.run ();
}