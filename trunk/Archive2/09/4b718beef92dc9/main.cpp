#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using boost::thread;
using boost::asio::io_service;

int main() {
    io_service svc;
    int num_events = 0;

    auto work = boost::make_shared<io_service::work>(svc); // keep svc running
    boost::thread thread(boost::bind(&io_service::run, &svc));

    for (auto i = 0; i < 500000; ++i) {
        svc.post([&num_events,i]{
                std::cout << "got event (" << i << ")" << std::endl;
                ++num_events;
                });
    }

    work.reset();
    thread.join();

    std::cout << "Check: " << num_events << " events counted\n";
}
