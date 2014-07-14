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
    int ch;
    int i;
    boost::asio::io_service ioservice;
    boost::thread_group group;

    boost::optional<boost::asio::io_service::work> work(boost::asio::io_service::work{ioservice});

    for(i=0; i<4; i++) {
        group.create_thread(
            boost::bind(&boost::asio::io_service::run, &ioservice)
        );
    }

    ch=0;
    while(ch <= 5) {
        ch++;
        std::cout << "in main" << boost::this_thread::get_id() << std::endl;
        for(i=0; i<5; i++) {
            ioservice.post(boost::bind(dowork,10));
        }
        std::cout << "size=" << group.size() <<std::endl;
        work.reset();
        ioservice.reset();
        ioservice.run();
    }
}
