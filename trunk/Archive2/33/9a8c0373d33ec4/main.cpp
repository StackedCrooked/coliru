#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

boost::atomic_int tid_gen(0);

void dowork(int i) {
    thread_local int tid = ++tid_gen;
    std::cout << "hello";
    std::cout << " thread ID :" << tid << "\n";
}

int main() {
    boost::asio::io_service ioservice;
    boost::thread_group group;

    boost::optional<boost::asio::io_service::work> work(boost::asio::io_service::work{ioservice});

    for(size_t i=0; i<boost::thread::hardware_concurrency(); i++) {
        group.create_thread(
            boost::bind(&boost::asio::io_service::run, &ioservice)
        );
    }

    std::cout << "in main thread size=" << group.size() <<std::endl;

    for(int i = 0; i <= 5; ++i) {
        for(int i=0; i<5; i++) {
            ioservice.post(boost::bind(dowork,10));
        }

        boost::this_thread::sleep_for(boost::chrono::milliseconds(600));
        std::cout << "waking up\n";
    }

    work.reset(); // allow threads to exit
    group.join_all(); // await proper thread shutdown
}
