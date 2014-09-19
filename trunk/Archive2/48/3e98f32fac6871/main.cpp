#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <iostream>

using boost::thread;
using boost::asio::io_service;

int main() {
    boost::asio::io_service     io_service;

    boost::asio::deadline_timer timer(io_service);
    timer.expires_at(boost::posix_time::pos_infin);

    boost::atomic_bool shutdown(false);

    int num_events = 0;
    auto waiter = [&timer, &num_events, &shutdown](boost::asio::yield_context context) {
        while (!shutdown) {
            std::cout << "waiting on event" << std::endl;

            boost::system::error_code e;
            timer.async_wait(context[e]);

            std::cout << "got event (" << e.message() << ")" << std::endl;
            ++num_events;
        }
    };

    boost::asio::spawn(io_service, std::move(waiter));
    boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service));

    for (auto i = 0; i < 5000; ++i) {
        io_service.post([&timer, i]{ 
                std::cout << i << std::endl;
                timer.cancel(); 
            });
    }

    io_service.post([&]{ 
            shutdown = true;
            timer.cancel();
        });

    thread.join();

    std::cout << "Check: " << num_events << " events counted\n";
}

