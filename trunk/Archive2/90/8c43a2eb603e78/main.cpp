#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>

#include <iostream>
using namespace std;

// Expected output:

// main coro starts
// in lambda inside subcoroutine - starts
// in lambda inside subcoroutine - starts
// in lambda inside subcoroutine - finishes
// in lambda inside subcoroutine - finishes
// main coro finishes

// Actual output:

// main coro starts
// in lambda inside subcoroutine - starts
// in lambda inside subcoroutine - starts
// main coro finishes <----
// in lambda inside subcoroutine - finishes
// in lambda inside subcoroutine - finishes

int main()
{
    using namespace boost::asio;

    io_service io;

    for (auto iter : {1,2,3})
    {
        spawn(io, [&](yield_context yield) {
            cout << "main coro starts\n";

            auto lambda = [&](yield_context yield) {
                cout << "in lambda inside subcoroutine - starts\n";
                steady_timer t(io, boost::chrono::milliseconds(100));
                t.async_wait(yield);
                cout << "in lambda inside subcoroutine - finishes\n";
            };

            // starting few coroutines
            spawn(yield, lambda);
            spawn(yield, lambda);
            spawn(yield, lambda);
            spawn(yield, lambda);
            spawn(yield, lambda);
            spawn(yield, lambda);

            // now I want to wait for all of them to finish before I do
            // some other work?
            // ???

            cout << "main coro finishes\n";
        });

        io.run(); // rendez-vous
        io.reset();
    }
}
