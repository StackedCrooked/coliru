#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


template<typename Callback>
void increment(int n, Callback callback)
{
    std::cout << "increment n=" << n << " tid=" << std::this_thread::get_id() << std::endl;
    std::thread([=] { usleep(rand() % 1000); callback(n + 1); }).detach();
}


int main()
{
    std::cout << "start" << std::endl;

    auto callback = [](int n) {

        std::cout << "main callback: n=" << n << " tid=" << std::this_thread::get_id() << std::endl;
    };

    boost::asio::io_service io;

    for (int i = 0; i != 10; ++i)
    {
        std::cout << "dispatch i=" << i << " tid=" << std::this_thread::get_id() << std::endl;
        io.dispatch([&, i]{ increment(i, [&](int n) {
            std::cout << "thread callback. n=" << n << " tid=" << std::this_thread::get_id() << std::endl;
            io.post(std::bind(callback, n)); });
        });
    }


    std::thread([&]{ std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << "Stopping io" << std::endl; io.stop(); }).detach();

    boost::asio::io_service::work w(io);
    io.run();
}
