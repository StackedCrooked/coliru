// Compile with: g++ -std=c++11 main.cpp -lpthread -lboost_system
#include <memory>
#include <functional>
#include <thread>
#include <future>
#include <cassert>
#include <string>

#include <boost/asio.hpp>

int main(int argc, char *argv[]) {
    boost::asio::io_service ioService;
    std::unique_ptr<boost::asio::io_service::work> work(new boost::asio::io_service::work(ioService));
    std::thread ioThread([&] () {
        ioService.run();
    });
    

    for (int i=0; i<1000; i++) {
        std::shared_ptr<std::promise<bool>> prom(new std::promise<bool>());
        std::future<bool> fut = prom->get_future();
        ioService.post([prom]() {
            prom->set_value(true);
        });

        assert(fut.get());
    }

    work.reset();
    ioThread.join();
}